﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AICharacter.h"

#include "AIController.h"
#include "AR_AttributeComponent.h"
#include "AR_StringLibrary.h"
#include "BrainComponent.h"
#include "WAR_WorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AAR_AICharacter::AAR_AICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetupComponents();
}

UAR_AttributeComponent* AAR_AICharacter::GetAttributeComponent()
{
	return AttributeComponent;
}

void AAR_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ensure(PawnSensingComponent))
	{
		PawnSensingComponent -> OnSeePawn.AddDynamic(this, &ThisClass::OnSeePawn);
	}
}

void AAR_AICharacter::SetupComponents()
{
	if (!PawnSensingComponent)
	{
		PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

		if (ensure(PawnSensingComponent))
		{
			AddOwnedComponent(PawnSensingComponent);
		}
	}

	if (!AttributeComponent)
	{
		AttributeComponent = CreateDefaultSubobject<UAR_AttributeComponent>(TEXT("Attribute Component"));

		if (ensure(AttributeComponent))
		{
			AddOwnedComponent(AttributeComponent);
		}
	}

	AutoPossessAI = EAutoPossessAI::Spawned;
}

void AAR_AICharacter::OnSeePawn(APawn* Pawn)
{
	if (Execute_GetIsAlive(Pawn))
	{
		SetTarget(Pawn);
	}
}

void AAR_AICharacter::DecreaseHealth_Implementation(const float& Amount)
{
}

void AAR_AICharacter::IncreaseHealth_Implementation(const float& Amount)
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> IncreaseHealth(Amount);
	}
}

void AAR_AICharacter::RestoreHealth_Implementation()
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> RestoreHealth();

		FString CurrentHealth = FString::Printf(TEXT("Health's been resored. Current Health: %f"), AttributeComponent -> GetCurrentHealth());
		
		DrawDebugString(GetWorld(), GetActorLocation(), CurrentHealth, nullptr, FColor::Green, 4.f, true);
	}
}

bool AAR_AICharacter::GetIsLowHealth_Implementation()
{
	if (ensure(AttributeComponent))
	{
		return  AttributeComponent -> GetIsLowHealth();
	}

	return false;
}

bool AAR_AICharacter::GetIsAlive_Implementation()
{
	if (ensure(AttributeComponent))
	{
		return AttributeComponent -> GetIsAlive();
	}

	return false;
}

float AAR_AICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Amount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ensure(AttributeComponent))
	{
		if (!HealthBarWidget && ensureMsgf(HealthBarWidgetClass, TEXT("AAR_AICharacter::TakeDamage: HealthBarWidgetClass is NULL")))
		{
			HealthBarWidget = CreateWidget<UWAR_WorldUserWidget>(GetWorld(), HealthBarWidgetClass);

			if (HealthBarWidget)
			{
				HealthBarWidget -> SetAttachedToActor(this);
				HealthBarWidget -> AddToViewport();
			}
		}
		
		GetMesh() -> SetScalarParameterValueOnMaterials("TimeToHit", GetWorld() -> GetTimeSeconds());
		
		if (!AttributeComponent -> DecreaseHealth(Amount))
		{
			AAIController* AIController = Cast<AAIController>(GetController());
			
			if (AIController)
			{
				AIController -> GetBrainComponent() -> StopLogic(TEXT("Killed"));
			}

			HealthBarWidget -> RemoveFromParent();
			GetMesh() -> SetAllBodiesSimulatePhysics(true);
			GetMesh() -> SetCollisionProfileName(TEXT("Ragdoll"));
		}
		else
		{
			SetTarget(DamageCauser);
		}
		
		FString CurrentHealth = FString::Printf(TEXT("Health's been resored. Current Health: %f"), AttributeComponent -> GetCurrentHealth());
	}
	
	return Amount;
}

void AAR_AICharacter::SetTarget(AActor* NewTarget)
{
	if (ensure(NewTarget))
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (ensure(AIController))
		{
			UBlackboardComponent* BlackboardComponent = AIController -> GetBlackboardComponent();

			if (ensure(BlackboardComponent))
			{
				BlackboardComponent -> SetValueAsObject(*FAIKeyLibrary::RMinionTargetActor, NewTarget);
			}
		}
	}
}
