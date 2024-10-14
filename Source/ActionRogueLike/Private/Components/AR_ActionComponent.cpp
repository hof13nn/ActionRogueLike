// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ActionComponent.h"

#include "AR_ActionBase.h"

UAR_ActionComponent::UAR_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAR_ActionComponent::OnRegister()
{
	Super::OnRegister();

	if (!ActionClassesArr.IsEmpty())
	{
		for (TSubclassOf<UAR_ActionBase> ActionClass : ActionClassesArr)
		{
			AddAction(ActionClass);
		}
	}
}

void UAR_ActionComponent::AddAction(TSubclassOf<UAR_ActionBase> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	if (UAR_ActionBase* NewAction = NewObject<UAR_ActionBase>(this, ActionClass))
	{
		ActionsArr.Emplace(NewAction);
	}
}

bool UAR_ActionComponent::StartActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UAR_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			Action -> StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UAR_ActionComponent::StopActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UAR_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			Action -> StopAction(Instigator);
			return true;
		}
	}

	return false;
}

