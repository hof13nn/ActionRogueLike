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
	AAR_ProjectileBase();

private:
	void SetupComponents();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
private:
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
