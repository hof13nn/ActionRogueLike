// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ProjectileBase.h"
#include "AR_ProjectileSpecial.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_ProjectileSpecial : public AAR_ProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_ProjectileSpecial();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void PostInitializeComponents() override;
	virtual void SetupComponents() override;
	
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	URadialForceComponent* RadialForceComponent;
	FTimerHandle ImpulseTimerHandle;
};
