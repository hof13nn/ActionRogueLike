// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AR_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAR_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetCredits(const int32& Value);
	void AddCredits(const int32& Value);
	UFUNCTION(BlueprintCallable)
	int32 GetCredits() const;

private:
	int32 Credits;
};
