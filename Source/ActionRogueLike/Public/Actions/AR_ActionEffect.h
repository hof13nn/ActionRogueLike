// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ActionBase.h"
#include "AR_ActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UAR_ActionEffect : public UAR_ActionBase
{
	GENERATED_BODY()
	
public:
	UAR_ActionEffect();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category="Effect")
	void ApplyPeriodicEffect(AActor* Instigator);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect", meta=(AllowPrivateAccess="true"))
	float Duration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect", meta=(AllowPrivateAccess="true"))
	float Rate;

protected:
	FTimerHandle EffectDuration_TimerHandle;
	FTimerHandle EffectRate_TimerHandle;
};
