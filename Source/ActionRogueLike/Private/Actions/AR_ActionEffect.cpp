// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ActionEffect.h"

#include "AR_ActionComponent.h"

UAR_ActionEffect::UAR_ActionEffect()
{
	bIsAutoStart = true;
	Duration = 0.f;
	Rate = 0.f;
}

void UAR_ActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (Duration > 0.f)
	{
		GetWorld() -> GetTimerManager().SetTimer(EffectDuration_TimerHandle, [&, Instigator]{ StopAction_Implementation(Instigator); }, Duration, false);

		if (Rate > 0.f)
		{
			GetWorld() -> GetTimerManager().SetTimer(EffectRate_TimerHandle, [&, Instigator]{ ApplyPeriodicEffect_Implementation(Instigator); }, Rate, true);
		}
	}
}

void UAR_ActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if (GetWorld() -> GetTimerManager().GetTimerRemaining(EffectRate_TimerHandle) < KINDA_SMALL_NUMBER)
	{
		ApplyPeriodicEffect_Implementation(Instigator);
	}
	
	Super::StopAction_Implementation(Instigator);

	GetWorld() -> GetTimerManager().ClearTimer(EffectDuration_TimerHandle);
	GetWorld() -> GetTimerManager().ClearTimer(EffectRate_TimerHandle);

	UAR_ActionComponent* AC = GetOwningComponent();

	if (AC)
	{
		AC -> RemoveAction(this);
	}
}

void UAR_ActionEffect::ApplyPeriodicEffect_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("%s::ApplyPeriodicEffect: Applying Effect: %s"), *GetNameSafe(this), *GetActionName().ToString());
}
