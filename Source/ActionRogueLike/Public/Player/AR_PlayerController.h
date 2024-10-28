// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AR_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAR_PlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, Category= UI)
	void OnAddCredits(AActor* Actor, const int32& Credits);
	UFUNCTION(BlueprintCallable)
	int32 GetCredits();
};
