// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_InteractableObjectBase.h"
#include "AR_HealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAR_HealthPotion : public AAR_InteractableObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_HealthPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	void SetActive(const bool& Value);
private:
	bool bIsInteractable;
	UPROPERTY(VisibleAnywhere)
	float HealthAmount;
	FTimerHandle InteractionDelayTimerHandle;
};
