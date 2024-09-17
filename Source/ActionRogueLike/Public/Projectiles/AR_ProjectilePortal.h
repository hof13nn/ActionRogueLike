// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ProjectileBase.h"
#include "AR_ProjectilePortal.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAR_ProjectilePortal : public AAR_ProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_ProjectilePortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupComponents() override;
	virtual void PostInitializeComponents() override;
	void ScheduleTeleportTimer();
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	FTimerHandle LifespanTimerHandle;
	FTimerHandle TeleportTimerHandle;

private:
	void Teleport();
};
