﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Character.h"
#include "AR_InputConfig.h"
#include "AR_PlayerController.h"
#include "AR_ProjectileBase.h"
#include "AR_StringLibrary.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/AR_InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


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
}

void AAR_Character::SetupCameraComponents()
{
	if (!SpringArmComponent)
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

		if (SpringArmComponent)
		{
			SpringArmComponent -> TargetArmLength = 500.f;
			SpringArmComponent -> bUsePawnControlRotation = true;
			SpringArmComponent -> SetupAttachment(RootComponent);
			
			if (!CameraComponent)
			{
				CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

				if (CameraComponent)
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

		if (InteractionComponent)
		{
			AddOwnedComponent(InteractionComponent);
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

// Called every frame
void AAR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			if (Config -> IA_Move.IsValid() && Config -> IA_Turn.Get())
			{
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Move.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleMove);
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Turn.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleTurn);
				EnhancedInputComponent.Get() -> BindAction(Config -> IA_Jump.Get(), ETriggerEvent::Started, this, &ThisClass::HandleJump);
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_Aim.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleAim);
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_Aim.Get(), ETriggerEvent::Completed, this, &ThisClass::HandleAim);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Fire.Get(), ETriggerEvent::Started, this, &ThisClass::HandlePrimaryAttack);
				EnhancedInputComponent.Get()  -> BindAction(Config -> IA_Interact.Get(), ETriggerEvent::Started, this, &ThisClass::HandleInteract);
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_Reload.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleReload);
				// EnhancedInputComponent.Get()  -> BindAction(InputConfig -> IA_SwitchWeapon.Get(), ETriggerEvent::Started, this, &ThisClass::HandleSwitchWeapon);
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

void AAR_Character::HandlePrimaryAttack(const FInputActionValue& InputActionValue)
{
	if (PrimaryAttackAnim)
	{
		PlayAnimMontage(PrimaryAttackAnim);

		if (GetWorld())
		{
			GetWorld() -> GetTimerManager().SetTimer(PrimaryAttackTimerHandle, this, &ThisClass::SpawnProjectile, .21f);
		}
	}
}

void AAR_Character::SpawnProjectile()
{
	if (GetMesh())
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Owner = this;

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
		const FVector SpawnLocation = GetMesh() -> GetSocketLocation(FSocketLibrary::CharacterProjectileSpawnSocket);
		FTransform Transform = FTransform(YawRotation, SpawnLocation);

		if (GetWorld())
		{
			if (AAR_ProjectileBase* ProjectileBase = GetWorld() -> SpawnActor<AAR_ProjectileBase>(AAR_ProjectileBase::StaticClass(), Transform, SpawnParameters))
			{
				ProjectileBase -> SetLifeSpan(5.f);
			}
		}
	}
}

void AAR_Character::HandleInteract(const FInputActionValue& InputActionValue)
{
	if (InteractionComponent)
	{
		InteractionComponent -> PrimaryInteract();
	}
}