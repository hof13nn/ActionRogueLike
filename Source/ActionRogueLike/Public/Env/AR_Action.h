// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_InteractableObjectBase.h"
#include "AR_Action.generated.h"

class UAR_ActionBase;

UCLASS()
class ACTIONROGUELIKE_API AAR_Action : public AAR_InteractableObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_Action();

	public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAR_ActionBase> ActionClass;
};
