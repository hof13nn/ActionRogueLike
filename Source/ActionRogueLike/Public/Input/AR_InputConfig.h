// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "AR_InputConfig.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UAR_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UAR_InputConfig();

	void SetupInputActions();
	
	UPROPERTY(VisibleDefaultsOnly, Category= "Context Settings")
	TWeakObjectPtr<UInputMappingContext> IMC_BaseContext;
	UPROPERTY(VisibleDefaultsOnly, Category= "Context Settings")
	int32 ContextPriority;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Move;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Turn;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_SwitchWeapon;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Fire;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_SpecialFire;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Teleport;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_ZoomIn;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_ZoomOut;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Interact;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Inventory;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TWeakObjectPtr<UInputAction> IA_Health;
};
