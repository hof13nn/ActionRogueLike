// Fill out your copyright notice in the Description page of Project Settings.

#include "AR_InputConfig.h"
#include "AR_StringLibrary.h"

UAR_InputConfig::UAR_InputConfig()
{
	ContextPriority = 0;
}

void UAR_InputConfig::SetupInputActions()
{
	IMC_BaseContext = LoadObject<UInputMappingContext>(this, *FPathLibrary::IMC_BaseContextPath);
	IA_Move = LoadObject<UInputAction>(this, *FPathLibrary::IA_MovePath);
	IA_Turn = LoadObject<UInputAction>(this, *FPathLibrary::IA_TurnPath);
	IA_Jump = LoadObject<UInputAction>(this, *FPathLibrary::IA_JumpPath);
	IA_SwitchWeapon = LoadObject<UInputAction>(this, *FPathLibrary::IA_SwitchWeaponPath);
	IA_Fire = LoadObject<UInputAction>(this, *FPathLibrary::IA_FirePath);
	IA_SpecialFire = LoadObject<UInputAction>(this, *FPathLibrary::IA_SpecialFire);
	IA_Teleport = LoadObject<UInputAction>(this, *FPathLibrary::IA_TeleportPath);
	IA_ZoomIn = LoadObject<UInputAction>(this, *FPathLibrary::IA_ZoomInPath);
	IA_ZoomOut = LoadObject<UInputAction>(this, *FPathLibrary::IA_ZoomOutPath);
	IA_Interact = LoadObject<UInputAction>(this, *FPathLibrary::IA_InteractPath);
	IA_Inventory = LoadObject<UInputAction>(this, *FPathLibrary::IA_InventoryPath);
	IA_Health = LoadObject<UInputAction>(this, *FPathLibrary::IA_HealthPath);
}