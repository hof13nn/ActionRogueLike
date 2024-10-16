﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AR_AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, TWeakObjectPtr<AActor>, Instigator, TWeakObjectPtr<UAR_AttributeComponent>, Component, float, NewValue, float, HealthDelta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UAR_AttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAR_AttributeComponent();

	UFUNCTION(BlueprintCallable)
	bool DecreaseHealth(const float& Amount);
	void IncreaseHealth(const float& Amount);
	void RestoreHealth();
	UFUNCTION(BlueprintCallable)
	bool GetNeedHealth();
	UFUNCTION(BlueprintCallable)
	bool GetIsLowHealth();
	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() const;
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	static UAR_AttributeComponent* GetAttributeComponent(AActor* TargetActor);
private:
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float MaxHealth;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
};
