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

	//Minion
	inline static const FName MinionMuzzleSocket = TEXT("Muzzle_01"); 
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
	inline static const FString IA_SprintPath = TEXT("/Game/Input/Actions/IA_Sprint.IA_Sprint");
	inline static const FString IA_FirePath = TEXT("/Game/Input/Actions/IA_Fire.IA_Fire");
	inline static const FString IA_SpecialFire = TEXT("/Game/Input/Actions/IA_SpecialFire.IA_SpecialFire");
	inline static const FString IA_TeleportPath = TEXT("/Game/Input/Actions/IA_Teleport.IA_Teleport");
	inline static const FString IA_ZoomInPath = TEXT("/Game/Input/Actions/IA_ZoomIn.IA_ZoomIn");
	inline static const FString IA_ZoomOutPath = TEXT("/Game/Input/Actions/IA_ZoomOut.IA_ZoomOut");
	inline static const FString IA_InteractPath = TEXT("/Game/Input/Actions/IA_Interact.IA_Interact");
	inline static const FString IA_InventoryPath = TEXT("/Game/Input/Actions/IA_Inventory.IA_Inventory");
	inline static const FString IA_HealthPath = TEXT("/Game/Input/Actions/Test/IA_Health.IA_Health");

	//Objects
	inline static const FString ProjectileMainPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_Projectile.P_Gideon_Primary_Projectile");
	inline static const FString ProjectileMainCastPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_MuzzleFlash.P_Gideon_Primary_MuzzleFlash");
	inline static const FString ProjectileMainExplosionPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitWorld.P_Gideon_Primary_HitWorld");
	inline static const FString ProjectileMainSoundPath = TEXT("/Game/BPs/Audio/SC_ProjectileMain.SC_ProjectileMain");
	inline static const FString ProjectileMainHitSoundPath = TEXT("/Game/BPs/Audio/SC_ProjectileMain_Impact.SC_ProjectileMain_Impact");
	inline static const FString ProjectileMainCameraShakePath = TEXT("/Game/ExampleContent/CameraShake/CamShake_TakeDamage_Small.CamShake_TakeDamage_Small_C");
	inline static const FString ProjectileSpecialPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Ultimate/FX/P_Gideon_Ultimate.P_Gideon_Ultimate");
	inline static const FString ProjectileSpecialExplosionPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitWorld.P_Gideon_Primary_HitWorld");
	inline static const FString ProjectileTeleportPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Portal/FX/P_Portal_Cast.P_Portal_Cast");
	inline static const FString ProjectileTeleportExplosionPath = TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Portal/FX/P_Portal_Entrance_Close.P_Portal_Entrance_Close");

	//AI
	inline static const FString RMinionBTPath = TEXT("/Game/BPs/AI/BT_Minion_Ranged_01.BT_Minion_Ranged_01");

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

class ACTIONROGUELIKE_API FAIKeyLibrary
{
public:
	inline static const FString RMinionMoveToLoc = TEXT("MoveToLoc");
	inline static const FString RMinionTargetActor = TEXT("TargetActor");
};

class ACTIONROGUELIKE_API FActionNamesLibrary
{
public:
	//Player
	inline static FName Sprint = TEXT("Sprint");
	inline static FName PrimaryAttack = TEXT("Primary Attack");
	inline static FName SecondaryAttack = TEXT("Secondary Attack");
	inline static FName DashAttack = TEXT("Dash Attack");
	// inline static FName CharacterProjectileSpawnSocket = TEXT("Muzzle_01");
	// inline static FName CharacterGroundSocket = TEXT("GroundSocket");
	// inline static FName CharacterBodySocket = TEXT("BodySocket");
	// inline static FName CharacterHeadSocket = TEXT("HeadSocket");
	// inline static FName WeaponProjectileSpawn = TEXT("ProjectileSpawn");
	// inline static FName WeaponEjectableMeshSpawn = TEXT("EjectableMeshSpawn");
};