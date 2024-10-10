// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_CreditCoin.h"


// Sets default values
AAR_CreditCoin::AAR_CreditCoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsWithdraw = false;
	CreditsValue = 10;

	Tags.Emplace(TEXT("Coin"));
}

bool AAR_CreditCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	const bool bCanInteract = Super::Interact_Implementation(InstigatorPawn);

	if (bCanInteract)
	{
		Destroy();
	}

	return bCanInteract;
}

