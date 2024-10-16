// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ActionEffect.h"
#include "AR_ActionEffect_Burn.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UAR_ActionEffect_Burn : public UAR_ActionEffect
{
	GENERATED_BODY()

protected:
	virtual void ApplyPeriodicEffect_Implementation(AActor* Instigator) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Effect")
	float Damage;
};