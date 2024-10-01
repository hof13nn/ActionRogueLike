// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AR_AICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAR_AICharacter();

protected:
	virtual void PostInitializeComponents() override;
	void SetupComponents();
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	
private:
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComponent;
};
