﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AR_InteractionComponent.h"

#include "AR_Character.h"
#include "AR_GameplayInterface.h"
#include "WAR_WorldUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interaction Component"), ECVF_Cheat);

// Sets default values for this component's properties
UAR_InteractionComponent::UAR_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 500.f;
	TraceRadius = 30.f;
	FocusedActor = nullptr;
	QueryChannel = ECC_WorldDynamic;
	DefaultWidget = nullptr;
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

	FindBestInteract();
}

void UAR_InteractionComponent::FindBestInteract()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(QueryChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner -> GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceLength);

	TArray<FHitResult> HitResults;
	
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bIsHit = GetWorld() -> SweepMultiByObjectType(HitResults, EyeLocation, End, FQuat::Identity, QueryParams, Shape);
	FColor HitColor = bIsHit ? FColor::Green : FColor::Red;

	FocusedActor = nullptr;
	
	for (FHitResult Hit : HitResults)
	{
		if (CVarDebugDrawInteraction.GetValueOnGameThread())
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, HitColor, false, 2.f);
		}

		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor -> Implements<UAR_GameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (!DefaultWidget && ensure(DefaultWidgetClass))
		{
			DefaultWidget = CreateWidget<UWAR_WorldUserWidget>(GetWorld(), DefaultWidgetClass);

			if (DefaultWidget)
			{
				DefaultWidget -> SetAttachedToActor(FocusedActor);

				if (!DefaultWidget -> IsInViewport())
				{
					DefaultWidget -> AddToViewport();
				}
			}
		}
	}
	else
	{
		if (DefaultWidget)
		{
			DefaultWidget -> RemoveFromParent();
			DefaultWidget = nullptr;
		}
	}
}

void UAR_InteractionComponent::PrimaryInteract()
{
	if (!FocusedActor)
	{
		return;
	}
	
	APawn* Pawn = Cast<APawn>(GetOwner());

	IAR_GameplayInterface::Execute_Interact(FocusedActor, Pawn);
}
