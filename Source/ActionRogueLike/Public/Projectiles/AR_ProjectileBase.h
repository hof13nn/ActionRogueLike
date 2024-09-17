// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AR_ProjectileBase.generated.h"

class UParticleEmitter;
class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_ProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AAR_ProjectileBase();
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void SetupComponents();
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   FVector NormalImpulse, const FHitResult& Hit);
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystem;
	UPROPERTY(VisibleAnywhere)
	UParticleSystem* Explosion;
	UPROPERTY(VisibleAnywhere)
	FVector CachedLaunchPosition;
};
