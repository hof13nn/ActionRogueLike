// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AR_AIController.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAR_AIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTree* BehaviorTree;
};
