// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ActionEffect_Burn.h"

#include "AR_ActionComponent.h"
#include "Kismet/GameplayStatics.h"

void UAR_ActionEffect_Burn::ApplyPeriodicEffect_Implementation(AActor* Instigator)
{
	Super::ApplyPeriodicEffect_Implementation(Instigator);

	if (UAR_ActionComponent* AC = GetOwningComponent())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: ApplyPeriodicEffect: Burning %s for %f"), *GetNameSafe(this), *GetNameSafe(AC -> GetOwner()), Damage);
		UGameplayStatics::ApplyDamage(AC -> GetOwner(), Damage, nullptr, Instigator, nullptr);
	}
}
