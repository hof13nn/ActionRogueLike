// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AR_GameMode.generated.h"

class AAR_InteractableObjectBase;

namespace EEnvQueryStatus
{
	enum Type : int;
}

class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAddCredits, AActor*, const int32&)

UCLASS()
class ACTIONROGUELIKE_API AAR_GameMode : public AGameMode
{
	GENERATED_BODY()

	AAR_GameMode();

public:
	virtual void StartPlay() override;
	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);
	
protected:
	void SetBotSpawnTimer();
	void SetItemSpawnTimer();
	void SpawnBots();
	void SpawnItem();
	UFUNCTION()
	void OnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void OnItemQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	bool CountAliveBots();
	bool CountExistItems();
	UFUNCTION()
	void RespawnPlayer(AController* Controller, AActor* OldPawn);
	
private:
	//Bots
	FTimerHandle SpawnBotsTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float BotSpawnTimerInterval;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> BotClass;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 MaxNumberOfBots;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
	//Items
	FTimerHandle SpawnItemsTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category="Consumables")
	float ItemSpawnTimerInterval;
	UPROPERTY(EditDefaultsOnly, Category="Consumables")
	UEnvQuery* SpawnItemQuery;
	UPROPERTY(EditDefaultsOnly, Category="Consumables")
	TArray<TSubclassOf<AAR_InteractableObjectBase>> ItemsArr;
	TSubclassOf<AAR_InteractableObjectBase> ItemToSpawn;
	UPROPERTY(EditDefaultsOnly, Category="Consumables")
	int32 MaxNumberOfPotions;
	UPROPERTY(EditDefaultsOnly, Category="Consumables")
	int32 MaxNumberOfCoins;
	UPROPERTY(EditDefaultsOnly, Category="Player")
	float RespawnDelay;

public:
	FOnAddCredits OnAddCredits;
};
