// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AR_GameMode.h"

#include "AR_AICharacter.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

AAR_GameMode::AAR_GameMode()
{
	SpawnTimerInterval = 2.f;
	MaxNumberOfBots = 10;
	SpawnBotQuery = nullptr;
	DifficultyCurve = nullptr;
}

void AAR_GameMode::StartPlay()
{
	Super::StartPlay();

	//SetBotSpawnTimer();
}

void AAR_GameMode::SetBotSpawnTimer()
{
	if (GetWorld())
	{
		GetWorld() -> GetTimerManager().SetTimer(SpawnBotsTimerHandle, this, &ThisClass::SpawnBots, SpawnTimerInterval, true);
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
				QueryInstance -> GetOnQueryFinishedEvent().AddDynamic(this, &ThisClass::OnQueryCompleted);
			}
		}
	}
}

bool AAR_GameMode::CountAliveBots()
{
	int32 NumberOfAliveBots = 0;

	for (TActorIterator<AAR_AICharacter> It(GetWorld()); It; ++It)
	{
		AAR_AICharacter* Bot = *It;

		if (IAR_Damageable::Execute_GetIsAlive(Bot))
		{
			NumberOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Bots Alive: %i, Max Bots: %i"), NumberOfAliveBots, MaxNumberOfBots);

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

void AAR_GameMode::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
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
