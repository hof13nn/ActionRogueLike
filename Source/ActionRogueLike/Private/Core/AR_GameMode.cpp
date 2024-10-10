// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AR_GameMode.h"
#include "AR_AICharacter.h"
#include "AR_Character.h"
#include "AR_CreditCoin.h"
#include "AR_HealthPotion.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enabling bots spawning via timer"), ECVF_Cheat);

AAR_GameMode::AAR_GameMode()
{
	BotSpawnTimerInterval = 2.f;
	MaxNumberOfBots = 10;
	SpawnBotQuery = nullptr;
	DifficultyCurve = nullptr;

	ItemSpawnTimerInterval = 5.f;
	SpawnItemQuery = nullptr;
	MaxNumberOfPotions = 2;
	MaxNumberOfCoins = 5;
	
	RespawnDelay = 5.f;
}

void AAR_GameMode::StartPlay()
{
	Super::StartPlay();

	SetBotSpawnTimer();
	SetItemSpawnTimer();
}


void AAR_GameMode::SetBotSpawnTimer()
{
	if (GetWorld())
	{
		GetWorld() -> GetTimerManager().SetTimer(SpawnBotsTimerHandle, this, &ThisClass::SpawnBots, BotSpawnTimerInterval, true);
	}
}

void AAR_GameMode::SetItemSpawnTimer()
{
	if (GetWorld())
	{
		GetWorld() -> GetTimerManager().SetTimer(SpawnItemsTimerHandle, this, &ThisClass::SpawnItem, ItemSpawnTimerInterval, true);
	}
}

void AAR_GameMode::SpawnItem()
{
	if (CountExistItems())
	{
		if (ensureMsgf(SpawnItemQuery, TEXT("AAR_GameMode::SpawnBots: SpawnBotQuery is NULL")))
		{
			if (UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnItemQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr))
			{
				QueryInstance -> GetOnQueryFinishedEvent().AddDynamic(this, &ThisClass::OnItemQueryCompleted);
			}
		}
	}
}

bool AAR_GameMode::CountExistItems()
{
	ItemToSpawn = ItemsArr[FMath::RandRange(0, ItemsArr.Num() - 1)];
	
	if (AActor* Actor = GetWorld() -> SpawnActor(ItemToSpawn))
	{
		int32 Counter = 0;
		
		if (Cast<AAR_HealthPotion>(Actor))
		{
			for (TActorIterator<AAR_HealthPotion> It(GetWorld()); It; ++It)
			{
				if (*It != Actor)
				{
					Counter++;
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("Potions Exist: %i, Max Potions: %i"), Counter, MaxNumberOfPotions);
		
			if (Counter >= MaxNumberOfPotions)
			{
				Actor -> Destroy();
				return false;
			}

			Actor -> Destroy();
			return true;
		
		}
		if (Cast<AAR_CreditCoin>(Actor))
		{
			for (TActorIterator<AAR_CreditCoin> It(GetWorld()); It; ++It)
			{
				if (*It != Actor)
				{
					Counter++;
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("Coins Exist: %i, Max Coins: %i"), Counter, MaxNumberOfCoins);
		
			if (Counter >= MaxNumberOfCoins)
			{
				Actor -> Destroy();
				return false;
			}

			Actor -> Destroy();
			return true;
		}

		UE_LOG(LogTemp, Error, TEXT("Couldn't count items"));
	
		return false;
	}

	return false;
}

void AAR_GameMode::OnItemQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	
	TArray<FVector> LocationsArr = QueryInstance -> GetResultsAsLocations();

	if (!LocationsArr.IsEmpty())
	{
		if (LocationsArr.IsValidIndex(0) && ensureMsgf(ItemToSpawn, TEXT(" AAR_GameMode::OnQueryCompleted: ItemToSpawn is NULL")))
		{
			GetWorld() -> SpawnActor<AActor>(ItemToSpawn, LocationsArr[0], FRotator::ZeroRotator);
		}
	}
}

void AAR_GameMode::SpawnBots()
{
	if (CountAliveBots())
	{
		if (ensureMsgf(SpawnBotQuery, TEXT("AAR_GameMode::SpawnBots: SpawnBotQuery is NULL")))
		{
			if (UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr))
			{
				QueryInstance -> GetOnQueryFinishedEvent().AddDynamic(this, &ThisClass::OnBotQueryCompleted);
			}
		}
	}
}

bool AAR_GameMode::CountAliveBots()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return false;
	}
	
	int32 NumberOfAliveBots = 0;

	for (TActorIterator<AAR_AICharacter> It(GetWorld()); It; ++It)
	{
		AAR_AICharacter* Bot = *It;

		if (IAR_Damageable::Execute_GetIsAlive(Bot))
		{
			NumberOfAliveBots++;
		}
	}

	if (ensureMsgf(DifficultyCurve, TEXT("AAR_GameMode::OnQueryCompleted: DifficultyCurve is NULL")))
	{
		MaxNumberOfBots = DifficultyCurve -> GetFloatValue(GetWorld() -> GetTimeSeconds());
		
		if (NumberOfAliveBots >= MaxNumberOfBots)
		{
			return false;
		}

		return true;
	}
	
	return true;
}

void AAR_GameMode::OnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	
	TArray<FVector> LocationsArr = QueryInstance -> GetResultsAsLocations();

	if (!LocationsArr.IsEmpty())
	{
		if (LocationsArr.IsValidIndex(0) && ensureMsgf(BotClass, TEXT(" AAR_GameMode::OnQueryCompleted: BotClass is NULL")))
		{
			GetWorld() -> SpawnActor<AActor>(BotClass, LocationsArr[0], FRotator::ZeroRotator);
		}
	}
}

void AAR_GameMode::RespawnPlayer(AController* Controller, AActor* OldPawn)
{
	if (Controller)
	{
		Controller -> UnPossess();
		RestartPlayer(Controller);
		OldPawn -> Destroy();
	}
}

void AAR_GameMode::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Warning, TEXT("AAR_GameMode::OnActorKilled:: %s killed %s"), *KillerActor -> GetActorLabel(), *VictimActor -> GetActorLabel());

	if (AAR_Character* Player = Cast<AAR_Character>(VictimActor))
	{
		FTimerHandle RespawnDelayTimerHandle;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayer", Player -> GetController(), Player);
		
		GetWorld() -> GetTimerManager().SetTimer(RespawnDelayTimerHandle, Delegate, RespawnDelay, false);
	}

	if (AAR_Character* Player = Cast<AAR_Character>(KillerActor))
	{
		OnAddCredits.Broadcast(Player, 5);
	}
}