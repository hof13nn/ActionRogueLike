﻿#pragma once

#include "CoreMinimal.h"
#include "AR_Damageable.h"
#include "AR_PlayerController.h"
#include "GameFramework/Character.h"
#include "AR_Character.generated.h"

class UAR_AttributeComponent;
class UAR_InteractionComponent;
class UAR_InputConfig;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API AAR_Character : public ACharacter, public IAR_Damageable
{
	GENERATED_BODY()
	AAR_Character();

private:
	void SetupCameraComponents();
	void SetupComponents();
	void AddMappingContext(const AAR_PlayerController* PlayerController, const UAR_InputConfig* Config);
	void SetupInputComponent(UInputComponent* PlayerInputComponent, const UAR_InputConfig* Config);
	void BindMovement(const TWeakObjectPtr<UEnhancedInputComponent>& EnhancedInputComponent, const UAR_InputConfig* Config);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleTurn(const FInputActionValue& InputActionValue);
	void HandleJump(const FInputActionValue& InputActionValue);
	void SpawnMainProjectile();
	void SpawnSpecialProjectile();
	void SpawnTeleportProjectile();
	FRotator CalculateRotation(const FVector& SpawnLocation) const;
	void HandlePrimaryAttack(const FInputActionValue& InputActionValue);
	void HandleSpecialAttack(const FInputActionValue& InputActionValue);
	void HandleTeleport(const FInputActionValue& InputActionValue);
	void HandleInteract(const FInputActionValue& InputActionValue);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
public:
	void SetupInput(const AAR_PlayerController* PlayerController);
	virtual void Tick(float DeltaTime) override;
	virtual void DecreaseHealth_Implementation(const float& Amount) override;
	virtual void IncreaseHealth_Implementation(const float& Amount) override;
	virtual bool GetNeedHealth_Implementation() override;
	virtual bool GetIsAlive_Implementation() override;
private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly)
	UAR_InteractionComponent* InteractionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UAR_AttributeComponent* AttributeComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Animations")
	UAnimMontage* PrimaryAttackAnim;
	FTimerHandle PrimaryAttackTimerHandle;
};