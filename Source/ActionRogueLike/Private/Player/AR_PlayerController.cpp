// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AR_PlayerController.h"

#include "AR_Character.h"
#include "AR_GameMode.h"
#include "AR_PlayerState.h"

void AAR_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void AAR_PlayerController::OnUnPossess()
{
	if (GetPawn())
	{
		GetPawn() -> Destroy();
	}
	
	Super::OnUnPossess();
}

void AAR_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AAR_GameMode* GM = GetWorld() -> GetAuthGameMode<AAR_GameMode>())
	{
		GM -> OnAddCredits.AddUObject(this, &ThisClass::OnAddCredits);
	}

	// if (AAR_Character* PlayerCharacter = Cast<AAR_Character>(GetPawn()))
	// {
	// 	PlayerCharacter -> SetupInput(this);
	// }
}

int32 AAR_PlayerController::GetCredits()
{
	if (AAR_PlayerState* PS = GetPlayerState<AAR_PlayerState>())
	{
		return PS -> GetCredits();
	}

	return -1;
}

void AAR_PlayerController::OnAddCredits_Implementation(AActor* Actor, const int32& Credits)
{
	if (GetPawn() == Actor)
	{
		if (AAR_PlayerState* PS = GetPlayerState<AAR_PlayerState>())
		{
			PS -> AddCredits(Credits);
		}
	}
}
