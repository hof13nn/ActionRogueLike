﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_HealthPotion.h"

#include "AR_Damageable.h"


// Sets default values
AAR_HealthPotion::AAR_HealthPotion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsInteractable = true;
	HealthAmount = 10.f;
}

// Called when the game starts or when spawned
void AAR_HealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAR_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (bIsInteractable && ensure(InstigatorPawn))
	{
		if (InstigatorPawn -> Implements<UAR_Damageable>())
		{
			if (IAR_Damageable::Execute_GetNeedHealth(InstigatorPawn))
			{
				IAR_Damageable::Execute_IncreaseHealth(InstigatorPawn, HealthAmount);

				SetActive(false);
				
				if (ensure(GetWorld()))
				{
					GetWorld() -> GetTimerManager().SetTimer(InteractionDelayTimerHandle, [&] { SetActive(true); }, 10.f, false);
				}
			}
		}
	}
}

void AAR_HealthPotion::SetActive(const bool& Value)
{
	bIsInteractable = Value;
	SetActorHiddenInGame(!Value);
}
