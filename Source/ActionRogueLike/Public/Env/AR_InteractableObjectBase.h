// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "AR_InteractableObjectBase.generated.h"

class UBoxComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_InteractableObjectBase : public AActor, public IAR_GameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_InteractableObjectBase();

protected:
	void SetupComponents();

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
