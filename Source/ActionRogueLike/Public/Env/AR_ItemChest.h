// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "AR_ItemChest.generated.h"

class UBoxComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_ItemChest : public AActor, public IAR_GameplayInterface
{
	GENERATED_BODY()
	AAR_ItemChest();

private:
	void SetupComponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Interact_Implementation(APawn* InstigatorPawn);
	
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LidMesh;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	float TargetPitch;
};
