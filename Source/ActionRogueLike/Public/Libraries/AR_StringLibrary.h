#pragma once

#include "CoreMinimal.h"


class ACTIONROGUELIKE_API FTagLibrary
{
public:
	inline static FName PlayerTag = TEXT("Player");
	inline static FName EnemyTag = TEXT("Enemy");
	inline static FName ProjectileTag = TEXT("Projectile");
	inline static FName PickupTag = TEXT("Pickup");
	inline static FName DamageableTag = TEXT("Damageable");
};

class ACTIONROGUELIKE_API FCollisionProfileLibrary
{
public:
	inline static FName ProjectileProfile = TEXT("Projectile");
	inline static FName EjectableMeshProfile = TEXT("EjectableMesh");
	inline static FName PickupProfile = TEXT("Pickup");
	inline static FName CharacterMovementCapsule = TEXT("CharacterMovementCapsule");
	inline static FName HitBox = TEXT("HitBox");
	inline static FName NoCollisionProfile = TEXT("NoCollision");
};

class ACTIONROGUELIKE_API FSocketLibrary
{
public:
	inline static FName CharacterWeaponSocket = TEXT("Weapon_R");
	inline static FName CharacterProjectileSpawnSocket = TEXT("Muzzle_01");
	inline static FName CharacterGroundSocket = TEXT("GroundSocket");
	inline static FName CharacterBodySocket = TEXT("BodySocket");
	inline static FName CharacterHeadSocket = TEXT("HeadSocket");
	inline static FName WeaponProjectileSpawn = TEXT("ProjectileSpawn");
	inline static FName WeaponEjectableMeshSpawn = TEXT("EjectableMeshSpawn");
};


class ACTIONROGUELIKE_API FPathLibrary
{
public: 
	//Input /Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'
	inline static const FString InputConfigPath = TEXT("/Game/Input/InputConfigData/DA_InputConfig_01.DA_InputConfig_01");
	inline static const FString IMC_BaseContextPath = TEXT("/Game/Input/Context/IMC_BaseContext.IMC_BaseContext");
	inline static const FString IA_MovePath = TEXT("/Game/Input/Actions/IA_Move.IA_Move");
	inline static const FString IA_TurnPath = TEXT("/Game/Input/Actions/IA_Turn.IA_Turn");
	inline static const FString IA_JumpPath = TEXT("/Game/Input/Actions/IA_Jump.IA_Jump");
	inline static const FString IA_SwitchWeaponPath = TEXT("/Game/Input/Actions/IA_SwitchWeapon.IA_SwitchWeapon");
	inline static const FString IA_FirePath = TEXT("/Game/Input/Actions/IA_Fire.IA_Fire");
	inline static const FString IA_ReloadPath = TEXT("/Game/Input/Actions/IA_Reload.IA_Reload");
	inline static const FString IA_AimPath = TEXT("/Game/Input/Actions/IA_Aim.IA_Aim");
	inline static const FString IA_ZoomInPath = TEXT("/Game/Input/Actions/IA_ZoomIn.IA_ZoomIn");
	inline static const FString IA_ZoomOutPath = TEXT("/Game/Input/Actions/IA_ZoomOut.IA_ZoomOut");
	inline static const FString IA_InteractPath = TEXT("/Game/Input/Actions/IA_Interact.IA_Interact");
	inline static const FString IA_InventoryPath = TEXT("/Game/Input/Actions/IA_Inventory.IA_Inventory");
	inline static const FString IA_HealthPath = TEXT("/Game/Input/Actions/Test/IA_Health.IA_Health");
	//Objects
	inline static const FString ProjectilePath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_Projectile.P_Gideon_Primary_Projectile");
	//UI
	inline static const FString PlayerHUDPath = TEXT("/Game/BPs/UI/Player/WBP_Player_HUD.WBP_Player_HUD_C");
	inline static const FString UnselectedWeaponPanelPath = TEXT("/Game/BPs/UI/Player/Objects/WBP_UnselectedWeaponPanel.WBP_UnselectedWeaponPanel_C");
	inline static const FString SelectedWeaponPanelPath = TEXT("/Game/BPs/UI/Player/Objects/WBP_SelectedWeaponPanel.WBP_SelectedWeaponPanel_C");
	inline static const FString DamageVisualWidgetPath = TEXT("/Game/BPs/UI/Enemies/WBP_DamageVisual.WBP_DamageVisual_C");
	inline static const FString PickupIconWidgetPath = TEXT("/Game/BPs/UI/Environment/WBP_PickupIcon.WBP_PickupIcon_C");
	inline static const FString EffectIconPath = TEXT("/Game/BPs/UI/Player/Objects/WBP_EffectIcon.WBP_EffectIcon_C");
	//Materials
	inline static const FString BloodPhyMaterialPath = TEXT("/Game/Assets/Environment/PhysMaterials/PM_Blood.PM_Blood");
	inline static const FString ShieldPhyMaterialPath = TEXT("/Game/Assets/Environment/PhysMaterials/PM_Shield.PM_Shield");
};