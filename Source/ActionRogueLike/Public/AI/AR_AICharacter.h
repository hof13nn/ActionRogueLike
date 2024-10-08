// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_Damageable.h"
#include "GameFramework/Character.h"
#include "AR_AICharacter.generated.h"

class UWAR_WorldUserWidget;
class UAR_AttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_AICharacter : public ACharacter, public IAR_Damageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAR_AICharacter();
	UAR_AttributeComponent* GetAttributeComponent();
protected:
	virtual void PostInitializeComponents() override;
	void SetupComponents();
	void SetTarget(AActor* NewTarget);
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	virtual void DecreaseHealth_Implementation(const float& Amount) override;
	virtual void IncreaseHealth_Implementation(const float& Amount) override;
	virtual void RestoreHealth_Implementation() override;
	virtual bool GetIsLowHealth_Implementation() override;
	virtual bool GetIsAlive_Implementation() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	UPROPERTY(VisibleAnywhere)
	UAR_AttributeComponent* AttributeComponent;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UWAR_WorldUserWidget> HealthBarWidgetClass;
	UPROPERTY()
	UWAR_WorldUserWidget* HealthBarWidget;
};
