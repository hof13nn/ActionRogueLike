// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AR_PlayerController.h"

#include "AR_Character.h"

void AAR_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AAR_Character* PlayerCharacter = Cast<AAR_Character>(InPawn))
	{
		PlayerCharacter -> SetupInput(this);
	}
}
