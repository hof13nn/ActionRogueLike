// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AR_InteractionComponent.h"

#include "AR_GameplayInterface.h"


// Sets default values for this component's properties
UAR_InteractionComponent::UAR_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	TraceLength = 500.f;
}

// Called when the game starts
void UAR_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAR_InteractionComponent::PrimaryInteract()
{
	if (GetWorld())
	{
		TWeakObjectPtr<APawn> MyOwner = Cast<APawn>(GetOwner());
		
		if (MyOwner.IsValid())
		{
			FHitResult HitResult;

			FCollisionObjectQueryParams QueryParams;
			QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

			FVector EyeLoc;
			FRotator EyeRot;
			MyOwner -> GetActorEyesViewPoint(EyeLoc, EyeRot);

			const bool bIsHit = GetWorld() -> LineTraceSingleByObjectType(HitResult, EyeLoc, EyeLoc + (EyeRot.Vector() * TraceLength), QueryParams);
			DrawDebugLine(GetWorld(), EyeLoc, EyeLoc + (EyeRot.Vector() * TraceLength), bIsHit ? FColor::Green : FColor::Red, false, 2.f, 0.f, 2.f);
			
			if (bIsHit)
			{
				TWeakObjectPtr<AActor> Actor = HitResult.GetActor();

				if (Actor.IsValid() && Actor.Get() -> Implements<UAR_GameplayInterface>())
				{
					IAR_GameplayInterface::Execute_Interact(Actor.Get(), MyOwner.Get());
				}
			}
		}
	}
}
