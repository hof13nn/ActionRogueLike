#pragma once

#include "CoreMinimal.h"
#include "AR_PlayerController.h"
#include "GameFramework/Character.h"
#include "AR_Character.generated.h"

class UAR_InputConfig;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API AAR_Character : public ACharacter
{
	GENERATED_BODY()
	AAR_Character();

private:
	void SetupCameraComponents();
	void AddMappingContext(const AAR_PlayerController* PlayerController, const UAR_InputConfig* Config);
	void SetupInputComponent(UInputComponent* PlayerInputComponent, const UAR_InputConfig* Config);
	void BindMovement(const TWeakObjectPtr<UEnhancedInputComponent>& EnhancedInputComponent, const UAR_InputConfig* Config);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleTurn(const FInputActionValue& InputActionValue);
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
public:
	void SetupInput(const AAR_PlayerController* PlayerController);
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
};