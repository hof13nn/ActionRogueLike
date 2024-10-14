// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Character.h"
#include "AR_ActionComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "AR_AttributeComponent.h"
#include "AR_GameMode.h"
#include "AR_InputConfig.h"
#include "AR_PlayerController.h"
#include "AR_ProjectileBase.h"
#include "AR_ProjectileMain.h"
#include "AR_ProjectilePortal.h"
#include "AR_ProjectileSpecial.h"
#include "AR_StringLibrary.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/AR_InteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

static TAutoConsoleVariable<bool> CVarDebugDrawProjectilePath(TEXT("su.ProjectilePathDebugDraw"), false, TEXT("Enable Debug Lines for Projectile Path}"), ECVF_Cheat);

// Sets default values
AAR_Character::AAR_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (GetCharacterMovement())
	{
		GetCharacterMovement() -> bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
	
	SetupCameraComponents();
	SetupComponents();

	Tags.Emplace(FTagLibrary::PlayerTag);
}

void AAR_Character::SetupCameraComponents()
{
	if (!SpringArmComponent)
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

		if (ensure(SpringArmComponent))
		{
			SpringArmComponent -> TargetArmLength = 500.f;
			SpringArmComponent -> bUsePawnControlRotation = true;
			SpringArmComponent -> SetupAttachment(RootComponent);
			
			if (!CameraComponent)
			{
				CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

				if (ensure(CameraComponent))
				{
					CameraComponent -> SetupAttachment(SpringArmComponent);
				}
			}
		}
	}
}

void AAR_Character::SetupComponents()
{
	if (!InteractionComponent)
	{
		InteractionComponent = CreateDefaultSubobject<UAR_InteractionComponent>(TEXT("Interaction Component"));

		if (ensure(InteractionComponent))
		{
			AddOwnedComponent(InteractionComponent);
		}
	}

	if (!AttributeComponent)
	{
		AttributeComponent = CreateDefaultSubobject<UAR_AttributeComponent>(TEXT("Attribute Component"));

		if (ensure(AttributeComponent))
		{
			AddOwnedComponent(AttributeComponent);
		}
	}

	if (!ActionComponent)
	{
		ActionComponent = CreateDefaultSubobject<UAR_ActionComponent>(TEXT("Action Component"));

		if (ensure(ActionComponent))
		{
			AddOwnedComponent(ActionComponent);
		}
	}
}

// Called when the game starts or when spawned
void AAR_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AAR_Character::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AAR_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Amount =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CanBeDamaged() && ensure(AttributeComponent))
	{
		GetMesh() -> SetScalarParameterValueOnMaterials("TimeToHit", GetWorld() -> GetTimeSeconds());
		
		if (!AttributeComponent -> DecreaseHealth(Amount))
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
			{
				DisableInput(PlayerController);

				if (ensure(GetCapsuleComponent()))
				{
					GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
				}
			}

			if (AAR_GameMode* GM = GetWorld() -> GetAuthGameMode<AAR_GameMode>())
			{
				GM -> OnActorKilled(this, DamageCauser);
			}
		}
	}

	return Amount;
}

// Called every frame
void AAR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAR_Character::DecreaseHealth_Implementation(const float& Amount)
{
	
}

void AAR_Character::IncreaseHealth_Implementation(const float& Amount)
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> IncreaseHealth(Amount);
	}
}

bool AAR_Character::GetNeedHealth_Implementation()
{
	if (ensure(AttributeComponent))
	{
		return AttributeComponent -> GetNeedHealth();
	}

	return false;
}

bool AAR_Character::GetIsAlive_Implementation()
{
	if (ensure(AttributeComponent))
	{
		return AttributeComponent -> GetIsAlive();
	}

	return false;
}

TWeakObjectPtr<UCameraComponent> AAR_Character::GetCameraComponent() const
{
	return TWeakObjectPtr<UCameraComponent>(CameraComponent);
}

FVector AAR_Character::GetPawnViewLocation() const
{
	return CameraComponent -> GetComponentLocation();
}

UAR_AttributeComponent* AAR_Character::GetAttributeComponent()
{
	return AttributeComponent;
}

void AAR_Character::SetupInput(const AAR_PlayerController* PlayerController)
{
	if (UAR_InputConfig* InputConfig = LoadObject<UAR_InputConfig>(this, *FPathLibrary::InputConfigPath))
	{
		InputConfig -> SetupInputActions();

		AddMappingContext(PlayerController, InputConfig);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AAR_Character::SetupInput: Input Config is NULL"));
	}
}

void AAR_Character::AddMappingContext(const AAR_PlayerController* PlayerController, const UAR_InputConfig* Config)
{
	if (PlayerController)
	{
		TWeakObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController -> GetLocalPlayer());
	
		if (Subsystem.IsValid())
		{
			if (Config)
			{
				if (Config -> IMC_BaseContext.IsValid())
				{
					Subsystem.Get() -> AddMappingContext(Config -> IMC_BaseContext.Get(), Config -> ContextPriority);

					SetupInputComponent(InputComponent, Config);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("AAR_Character::AddMappingContext: Input Mapping Context is NULL"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("AAR_Character::AddMappingContext: Input Config is NULL"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AAR_Character::AddMappingContext: Subsystem is NULL"));
		}
	}
}

void AAR_Character::SetupInputComponent(UInputComponent* PlayerInputComponent, const UAR_InputConfig* Config)
{
	if (PlayerInputComponent)
	{
		if (Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

			if (EnhancedInputComponent.IsValid())
			{
				BindMovement(EnhancedInputComponent, Config);
			}
		}
	}
}

void AAR_Character::BindMovement(const TWeakObjectPtr<UEnhancedInputComponent>& EnhancedInputComponent, const UAR_InputConfig* Config)
{
	if (EnhancedInputComponent.IsValid())
	{
		if (Config)
		{
			if (Config -> IA_Move.IsValid() && Config -> IA_Turn.IsValid() && Config -> IA_Jump.IsValid() && Config -> IA_Sprint.IsValid()
				&& Config -> IA_Fire.IsValid() && Config -> IA_SpecialFire.IsValid() && Config -> IA_Teleport.IsValid() && Config -> IA_Interact.IsValid())
			{
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Move.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleMove);
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Turn.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleTurn);
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Jump.Get(), ETriggerEvent::Started, this, &ThisClass::HandleJump);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Sprint.Get(), ETriggerEvent::Started, this, &ThisClass::HandleStartSprint);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Sprint.Get(), ETriggerEvent::Completed, this, &ThisClass::HandleStopSprint);
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_Aim.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleAim);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Fire.Get(), ETriggerEvent::Started, this, &ThisClass::HandlePrimaryAttack);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_SpecialFire.Get(), ETriggerEvent::Started, this, &ThisClass::HandleSpecialAttack);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Teleport.Get(), ETriggerEvent::Started, this, &ThisClass::HandleDash);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Interact.Get(), ETriggerEvent::Started, this, &ThisClass::HandleInteract);
	
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_Health.Get(), ETriggerEvent::Started, this, &ThisClass::HandleHealth);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AAR_Character::BindMovement: Input Config is NULL"));
		}
	}
}

void AAR_Character::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AAR_Character::HandleMove: Controller is NULL"));
	}
}

void AAR_Character::HandleTurn(const FInputActionValue& InputActionValue)
{
	const FVector2d TurnVector = InputActionValue.Get<FVector2d>();
	
	if (TurnVector.X != 0)
	{
		AddControllerYawInput(TurnVector.X);
	}

	if (TurnVector.Y != 0)
	{
		AddControllerPitchInput(TurnVector.Y);
	}
}

void AAR_Character::HandleJump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AAR_Character::HandleStartSprint(const FInputActionValue& InputActionValue)
{
	if (ensure(ActionComponent))
	{
		ActionComponent -> StartActionByName(this, FActionNamesLibrary::Sprint);
	}
}

void AAR_Character::HandleStopSprint(const FInputActionValue& InputActionValue)
{
	if (ensure(ActionComponent))
	{
		ActionComponent -> StopActionByName(this, FActionNamesLibrary::Sprint);
	}
}

void AAR_Character::HandlePrimaryAttack(const FInputActionValue& InputActionValue)
{
	if (ensure(ActionComponent))
	{
		ActionComponent -> StartActionByName(this, FActionNamesLibrary::PrimaryAttack);
	}
}

void AAR_Character::HandleSpecialAttack(const FInputActionValue& InputActionValue)
{
	if (ensure(ActionComponent))
	{
		ActionComponent -> StartActionByName(this, FActionNamesLibrary::SecondaryAttack);
	}
}

void AAR_Character::HandleDash(const FInputActionValue& InputActionValue)
{
	if (ensure(ActionComponent))
	{
		ActionComponent -> StartActionByName(this, FActionNamesLibrary::DashAttack);
	}
}

// void AAR_Character::SpawnMainProjectile()
// {
// 	if (GetMesh())
// 	{
// 		FActorSpawnParameters SpawnParameters;
// 		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		SpawnParameters.Owner = this;
// 		SpawnParameters.Instigator = this;
// 		
// 		const FVector SpawnLocation = GetMesh() -> GetSocketLocation(FSocketLibrary::CharacterProjectileSpawnSocket);
// 		const FRotator Rotation = CalculateRotation(SpawnLocation);
// 		const FTransform Transform = FTransform(Rotation, SpawnLocation);
//
// 		if (GetWorld())
// 		{
// 			if (!GetWorld() -> SpawnActor<AAR_ProjectileMain>(AAR_ProjectileMain::StaticClass(), Transform, SpawnParameters))
// 			{
// 				UE_LOG(LogTemp, Error, TEXT("AAR_Character::SpawnProjectile: Couldn't spawn Projectile"));
// 			}
// 			else
// 			{
// 				if (UParticleSystem* Cast = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileMainCastPath))
// 				{
// 					UGameplayStatics::SpawnEmitterAttached(Cast, GetMesh(), FSocketLibrary::CharacterProjectileSpawnSocket);
// 				}
// 			}
// 		}
// 	}
// }
//
// void AAR_Character::SpawnSpecialProjectile()
// {
// 	if (GetMesh())
// 	{
// 		FActorSpawnParameters SpawnParameters;
// 		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		SpawnParameters.Owner = this;
// 		SpawnParameters.Instigator = this;
// 		
// 		const FVector SpawnLocation = GetMesh() -> GetSocketLocation(FSocketLibrary::CharacterProjectileSpawnSocket);
// 		const FRotator Rotation = CalculateRotation(SpawnLocation);
// 		const FTransform Transform = FTransform(Rotation, SpawnLocation);
//
// 		if (GetWorld())
// 		{
// 			if (!GetWorld() -> SpawnActor<AAR_ProjectileBase>(AAR_ProjectileSpecial::StaticClass(), Transform, SpawnParameters))
// 			{
// 				UE_LOG(LogTemp, Error, TEXT("AAR_Character::SpawnProjectile: Couldn't spawn Projectile"));
// 			}
// 		}
// 	}
// }
//
// void AAR_Character::SpawnTeleportProjectile()
// {
// 	if (GetMesh())
// 	{
// 		FActorSpawnParameters SpawnParameters;
// 		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		SpawnParameters.Owner = this;
// 		SpawnParameters.Instigator = this;
// 		
// 		const FVector SpawnLocation = GetMesh() -> GetSocketLocation(FSocketLibrary::CharacterProjectileSpawnSocket);
// 		const FRotator Rotation = CalculateRotation(SpawnLocation);
// 		const FTransform Transform = FTransform(Rotation, SpawnLocation);
//
// 		if (GetWorld())
// 		{
// 			if (!GetWorld() -> SpawnActor<AAR_ProjectileBase>(AAR_ProjectilePortal::StaticClass(), Transform, SpawnParameters))
// 			{
// 				UE_LOG(LogTemp, Error, TEXT("AAR_Character::SpawnProjectile: Couldn't spawn Projectile"));
// 			}
// 		}
// 	}
// }
//
// FRotator AAR_Character::CalculateRotation(const FVector& SpawnLocation) const
// {
// 	if (GetWorld() && CameraComponent)
// 	{
// 		FHitResult HitResult;
//
// 		FCollisionObjectQueryParams QueryParams;
// 		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
// 		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
// 		
// 		const FVector StartLocation = CameraComponent -> GetComponentLocation();
// 		const FVector EndLocation = StartLocation + (CameraComponent -> GetForwardVector() * 5000.f);
// 		
// 		const bool bIsHit = GetWorld() -> LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, QueryParams);
//
// 		if (CVarDebugDrawProjectilePath.GetValueOnGameThread())
// 		{
// 			DrawDebugLine(GetWorld(), StartLocation, EndLocation, bIsHit ? FColor::Green : FColor::Red, false, 2.f, 0.f, 2.f);
// 		}
//
// 		return UKismetMathLibrary::FindLookAtRotation(SpawnLocation, bIsHit ? HitResult.Location : EndLocation);
// 	}
//
// 	return FRotator::ZeroRotator;
// }

void AAR_Character::HandleInteract(const FInputActionValue& InputActionValue)
{
	if (InteractionComponent)
	{
		InteractionComponent -> PrimaryInteract();
	}
}
