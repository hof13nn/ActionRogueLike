// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_InteractableObjectBase.h"
#include "AR_CreditCoin.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAR_CreditCoin : public AAR_InteractableObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_CreditCoin();

protected:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
