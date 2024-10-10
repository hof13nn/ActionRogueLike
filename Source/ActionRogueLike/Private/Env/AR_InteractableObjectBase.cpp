// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_InteractableObjectBase.h"

#include "AR_PlayerController.h"
#include "AR_PlayerState.h"
#include "Components/BoxComponent.h"


// Sets default values
AAR_InteractableObjectBase::AAR_InteractableObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();

	bIsWithdraw = true;
	CreditsValue = 0;
}

void AAR_InteractableObjectBase::SetupComponents()
{
	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (ensure(BoxComponent))
		{
			RootComponent = BoxComponent;
		}
	}

	if (!Mesh)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

		if (ensure(Mesh))
		{
			Mesh -> SetupAttachment(RootComponent);
		}
	}
}

bool AAR_InteractableObjectBase::Interact_Implementation(APawn* InstigatorPawn)
{
	return bIsWithdraw ? WithdrawCredits(InstigatorPawn) : AddCredits(InstigatorPawn);
}

UClass* AAR_InteractableObjectBase::GetObjectClass()
{
	return StaticClass();
}

bool AAR_InteractableObjectBase::WithdrawCredits(APawn* InstigatorPawn) const
{
	if (AAR_PlayerController* Controller = Cast<AAR_PlayerController>(InstigatorPawn -> GetController()))
	{
		if (AAR_PlayerState* PlayerState = Controller -> GetPlayerState<AAR_PlayerState>())
		{
			if (PlayerState -> GetCredits() >= CreditsValue)
			{
				Controller -> OnAddCredits(InstigatorPawn, -CreditsValue);

				return true;
			}

			return false;
		}

		return false;
	}

	return false;
}

bool AAR_InteractableObjectBase::AddCredits(APawn* InstigatorPawn) const
{
	if (AAR_PlayerController* Controller = Cast<AAR_PlayerController>(InstigatorPawn -> GetController()))
	{
		Controller -> OnAddCredits(InstigatorPawn, CreditsValue);

		return true;
	}

	return false;
}
