// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_HealthPotion.h"
#include "AR_Damageable.h"


// Sets default values
AAR_HealthPotion::AAR_HealthPotion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsWithdraw = true;
	HealthAmount = 10.f;
	CreditsValue = 10.f;

	Tags.Emplace(TEXT("Potion"));
}

// Called when the game starts or when spawned
void AAR_HealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAR_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		if (IAR_Damageable::Execute_GetNeedHealth(InstigatorPawn))
		{
			Super::Interact_Implementation(InstigatorPawn);
			IAR_Damageable::Execute_IncreaseHealth(InstigatorPawn, HealthAmount);

			Destroy();
		}
	}
}

void AAR_HealthPotion::SetActive(const bool& Value)
{
	SetActorEnableCollision(Value);

	if (ensure(RootComponent))
	{
		RootComponent -> SetVisibility(Value, true);
	}
}



