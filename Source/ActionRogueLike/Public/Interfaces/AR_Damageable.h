﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AR_Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAR_Damageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROGUELIKE_API IAR_Damageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DecreaseHealth(AActor* InstigatorActor, const float& Amount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncreaseHealth(const float& Amount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RestoreHealth();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetNeedHealth();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsLowHealth();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsAlive();
};