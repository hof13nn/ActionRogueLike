// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ActionEffect.h"
#include "AR_ActionEffect_Thorns.generated.h"

class UAR_AttributeComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UAR_ActionEffect_Thorns : public UAR_ActionEffect
{
	GENERATED_BODY()

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAR_AttributeComponent* OwningComp, float NewValue, float HealthDelta);
};
