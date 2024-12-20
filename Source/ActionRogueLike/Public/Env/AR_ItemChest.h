﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "AR_ItemChest.generated.h"

class UTimelineComponent;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_LidOpened();
public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* LidMesh;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	UPROPERTY(ReplicatedUsing="OnRep_LidOpened")
	bool bIsOpen;
	UPROPERTY(EditAnywhere)
	UTimelineComponent* TimelineTemplate;
};
