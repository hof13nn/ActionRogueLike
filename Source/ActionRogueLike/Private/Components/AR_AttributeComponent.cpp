// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AttributeComponent.h"


// Sets default values for this component's properties
UAR_AttributeComponent::UAR_AttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}

bool UAR_AttributeComponent::DecreaseHealth(const float& Amount)
{
	CurrentHealth = FMath::Max(0, CurrentHealth - Amount);

	OnHealthChanged.Broadcast(nullptr, this, CurrentHealth, CurrentHealth / MaxHealth);
	return true;
}

void UAR_AttributeComponent::IncreaseHealth()
{
	
}