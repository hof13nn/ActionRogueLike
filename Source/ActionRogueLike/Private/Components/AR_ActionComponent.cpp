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
			AddAction(GetOwner(), ActionClass);
		}
	}
}

void UAR_ActionComponent::AddAction(AActor* Instigator, TSubclassOf<UAR_ActionBase> ActionClass)
{
	if (!ActionClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s::AddAction: Action Class is NULL"), *GetNameSafe(GetOwner()));
		return;
	}

	if (UAR_ActionBase* NewAction = NewObject<UAR_ActionBase>(this, ActionClass))
	{
		ActionsArr.Emplace(NewAction);

		if (NewAction -> GetIsAutoStart() && ensure(NewAction -> CanStart(Instigator)))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s::AddAction: Starting %s"), *GetNameSafe(GetOwner()), *NewAction -> GetActionName().ToString());
			NewAction -> StartAction(Instigator);
		}
	}
}

void UAR_ActionComponent::RemoveAction(UAR_ActionBase* Action)
{
	if (Action && !Action -> GetIsActive())
	{
		ActionsArr.Remove(Action);
	}
}

bool UAR_ActionComponent::StartActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UAR_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			if (!Action -> CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to Start %s"), *ActionName.ToString());
				GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
				return false;
			}
			
			Action -> StartAction(Instigator);
			return true;
		}
	}

	FString FailedMsg = FString::Printf(TEXT(" %s deesn't exist"), *ActionName.ToString());
	GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
	
	return false;
}

bool UAR_ActionComponent::StopActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UAR_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			if (Action -> GetIsActive())
			{
				Action -> StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

void UAR_ActionComponent::AddTags(const FGameplayTagContainer& Tags)
{
	ActiveGameplayTags.AppendTags(Tags);
}

void UAR_ActionComponent::AddTag(const FGameplayTag& Tag)
{
	ActiveGameplayTags.AddTag(Tag);
}

void UAR_ActionComponent::RemoveTags(const FGameplayTagContainer& Tags)
{
	ActiveGameplayTags.RemoveTags(Tags);
}

void UAR_ActionComponent::RemoveTag(const FGameplayTag& Tag)
{
	ActiveGameplayTags.RemoveTag(Tag);
}

bool UAR_ActionComponent::HasTags(const FGameplayTagContainer& Tags)
{
	return ActiveGameplayTags.HasAny(Tags);
}

bool UAR_ActionComponent::HasTag(const FGameplayTag& Tag)
{
	return ActiveGameplayTags.HasTag(Tag);
}


// FGameplayTagContainer& UAR_ActionComponent::GetActiveGameplayTags()
// {
// 	return ActiveGameplayTags;
// }

