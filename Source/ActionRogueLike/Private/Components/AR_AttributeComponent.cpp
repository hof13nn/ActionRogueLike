// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AttributeComponent.h"

#include "AR_AICharacter.h"
#include "AR_Character.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UAR_AttributeComponent::UAR_AttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;

	SetIsReplicatedByDefault(true);
}

bool UAR_AttributeComponent::DecreaseHealth(AActor* InstigatorActor, const float& Amount)
{
	CurrentHealth = FMath::Max(0, CurrentHealth - Amount);

	//OnHealthChanged.Broadcast(nullptr, this, CurrentHealth, CurrentHealth / MaxHealth);
	MulticastHealthChanged(InstigatorActor, CurrentHealth, CurrentHealth / MaxHealth);
	return GetIsAlive();
}

void UAR_AttributeComponent::IncreaseHealth(const float& Amount)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + Amount);
	OnHealthChanged.Broadcast(nullptr, this, CurrentHealth, CurrentHealth / MaxHealth);
}

void UAR_AttributeComponent::RestoreHealth()
{
	CurrentHealth = MaxHealth;
	OnHealthChanged.Broadcast(nullptr, this, CurrentHealth, CurrentHealth / MaxHealth);
}

bool UAR_AttributeComponent::GetNeedHealth()
{
	return CurrentHealth < MaxHealth;
}

bool UAR_AttributeComponent::GetIsLowHealth()
{
	return CurrentHealth / MaxHealth <= 0.3f;
}

bool UAR_AttributeComponent::GetIsAlive() const
{
	return CurrentHealth > 0.f;
}

float UAR_AttributeComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UAR_AttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

UAR_AttributeComponent* UAR_AttributeComponent::GetAttributeComponent(AActor* TargetActor)
{
	if (TargetActor)
	{
		if (AAR_Character* OwningChar = Cast<AAR_Character>(TargetActor))
		{
			return OwningChar -> GetAttributeComponent();
		}
		if (AAR_AICharacter* OwningChar = Cast<AAR_AICharacter>(TargetActor))
		{
			return OwningChar -> GetAttributeComponent();
		}
	}

	return nullptr;
}

void UAR_AttributeComponent::MulticastHealthChanged_Implementation(AActor* Instigator, float NewValue, float HealthDelta)
{
	OnHealthChanged.Broadcast(Instigator, this, NewValue, HealthDelta);
}

void UAR_AttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAR_AttributeComponent, CurrentHealth);
	DOREPLIFETIME(UAR_AttributeComponent, MaxHealth);

	//DOREPLIFETIME_CONDITION(UAR_AttributeComponent, MaxHealth, COND_OwnerOnly);
}
