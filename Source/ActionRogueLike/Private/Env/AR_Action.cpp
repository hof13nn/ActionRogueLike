// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Action.h"

#include "AR_ActionComponent.h"
#include "AR_Character.h"


// Sets default values
AAR_Action::AAR_Action()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAR_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	if (UAR_ActionComponent* AC = Cast<AAR_Character>(InstigatorPawn) -> GetActionComponent())
	{
		if (AC -> GetAction(ActionClass))
		{
			return;
		}

		AC -> AddAction(InstigatorPawn, ActionClass);
		Destroy();
	}
}