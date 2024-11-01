// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ActionEffect_Thorns.h"

#include "AR_ActionComponent.h"
#include "AR_AttributeComponent.h"
#include "Kismet/GameplayStatics.h"

void UAR_ActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (UAR_AttributeComponent* AttributeComponent = UAR_AttributeComponent::GetAttributeComponent(GetOwningComponent() -> GetOwner()))
	{
		AttributeComponent -> OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	}
	
}

void UAR_ActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (UAR_AttributeComponent* AttributeComponent = UAR_AttributeComponent::GetAttributeComponent(GetOwningComponent() -> GetOwner()))
	{
		AttributeComponent -> OnHealthChanged.RemoveDynamic(this, &ThisClass::OnHealthChanged);
	}
}

void UAR_ActionEffect_Thorns::OnHealthChanged(AActor* InstigatorActor, UAR_AttributeComponent* OwningComp,
	float NewValue, float HealthDelta)
{
	AActor* OwningActor = GetOwningComponent() -> GetOwner();

	if (NewValue > 0.f && OwningActor != InstigatorActor)
	{
		int32 ReflectedAmount = FMath::RoundToInt(NewValue * .25f);

		if (ReflectedAmount == 0)
		{
			return;
		}

		UGameplayStatics::ApplyDamage(InstigatorActor, ReflectedAmount, nullptr, OwningActor, nullptr);
	}
}
