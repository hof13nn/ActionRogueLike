// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AR_GameMode.generated.h"

namespace EEnvQueryStatus
{
	enum Type : int;
}

class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAR_GameMode : public AGameMode
{
	GENERATED_BODY()

	AAR_GameMode();
	void SetBotSpawnTimer();

public:
	virtual void StartPlay() override;

	
protected:
	void SpawnBots();
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	bool CountAliveBots();
private:
	FTimerHandle SpawnBotsTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> BotClass;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 MaxNumberOfBots;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
};
