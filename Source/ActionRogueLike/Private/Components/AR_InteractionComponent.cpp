// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AR_InteractionComponent.h"

#include "AR_Character.h"
#include "AR_GameplayInterface.h"
#include "Camera/CameraComponent.h"


// Sets default values for this component's properties
UAR_InteractionComponent::UAR_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TraceLength = 5000.f;
}

// Called when the game starts
void UAR_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAR_InteractionComponent::OnRegister()
{
	Super::OnRegister();

	Owner = Cast<AAR_Character>(GetOwner());
	
	if (Owner.IsValid())
	{
		CameraComponent = Owner.Get() -> GetCameraComponent();
	}
}

void UAR_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (ensure(CameraComponent.Get()))
	// {
	// 	//Viewport Size
	// 	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	// 	//Viewport Center!            
	// 	const FVector2D  ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	// 	
	// 	const FVector StartLocation = CameraComponent.Get() -> GetComponentLocation();
	// 	const FVector EndLocation = FVector(ViewportCenter.X, ViewportCenter.Y, StartLocation.Z) * TraceLength;
	//
	// 	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, 2.f, 0.f, 2.f);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("UAR_InteractionComponent::TickComponent: No Camera"));
	// }
}

void UAR_InteractionComponent::PrimaryInteract()
{
	if (GetWorld())
	{
		if (Owner.IsValid() && ensure(CameraComponent.Get()))
		{
			FHitResult HitResult;

			FCollisionObjectQueryParams QueryParams;
			QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
			
			const FVector StartLocation = CameraComponent.Get() -> GetComponentLocation();
			const FVector EndLocation = StartLocation + (CameraComponent.Get() -> GetForwardVector() * TraceLength);
		
			const bool bIsHit = GetWorld() -> LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, QueryParams);
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, bIsHit ? FColor::Green : FColor::Red, false, 2.f, 0.f, 2.f);
			
			if (bIsHit)
			{
				TWeakObjectPtr<AActor> Actor = HitResult.GetActor();

				if (Actor.IsValid() && Actor.Get() -> Implements<UAR_GameplayInterface>())
				{
					IAR_GameplayInterface::Execute_Interact(Actor.Get(), Owner.Get());
				}
			}
		}
	}
}
