// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AR_GameMode.h"

#include "AR_AICharacter.h"
#include "AR_Character.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enabling bots spawning via timer"), ECVF_Cheat);

AAR_GameMode::AAR_GameMode()
{
	SpawnTimerInterval = 2.f;
	MaxNumberOfBots = 10;
	SpawnBotQuery = nullptr;
	DifficultyCurve = nullptr;

	RespawnDelay = 5.f;
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

void AAR_GameMode::RespawnPlayer(AController* Controller)
{
	if (Controller)
	{
		Controller -> UnPossess();
		RestartPlayer(Controller);
	}
}

void AAR_GameMode::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Warning, TEXT("AAR_GameMode::OnActorKilled:: %s killed %s"), *KillerActor -> GetActorLabel(), *VictimActor -> GetActorLabel());

	if (AAR_Character* Player = Cast<AAR_Character>(VictimActor))
	{
		FTimerHandle RespawnDelayTimerHandle;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayer", Player -> GetController());
		
		GetWorld() -> GetTimerManager().SetTimer(RespawnDelayTimerHandle, Delegate, RespawnDelay, false);
	}
}