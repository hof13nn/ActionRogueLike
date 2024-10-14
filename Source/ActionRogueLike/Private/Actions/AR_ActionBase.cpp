// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ActionBase.h"

void UAR_ActionBase::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("UAR_ActionBase::StartAction: Started: %s"), *GetNameSafe(this));
}

void UAR_ActionBase::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("UAR_ActionBase::StopAction: Stopped: %s"), *GetNameSafe(this));
}

FName UAR_ActionBase::GetActionName() const
{
	return Name;
}

UWorld* UAR_ActionBase::GetWorld() const
{
	if (const UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp -> GetWorld();
	}
	
	return nullptr;
}
