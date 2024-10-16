// Fill out your copyright notice in the Description page of Project Settings.

#include "AR_ActionBase.h"
#include "AR_ActionComponent.h"

bool UAR_ActionBase::CanStart_Implementation(AActor* Instigator)
{
	if (bIsActive)
	{
		return false;
	}

	UAR_ActionComponent* AC = GetOwningComponent();
	
	return !AC -> HasTags(BlockedTags);
}

void UAR_ActionBase::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("UAR_ActionBase::StartAction: Started: %s"), *GetNameSafe(this));

	UAR_ActionComponent* AC = GetOwningComponent();
	AC -> AddTags(GrantsTags);
	bIsActive = true;
}

void UAR_ActionBase::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("UAR_ActionBase::StopAction: Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsActive);
	
	UAR_ActionComponent* AC = GetOwningComponent();
	AC -> RemoveTags(GrantsTags);
	bIsActive = false;
}

FName UAR_ActionBase::GetActionName() const
{
	return Name;
}

bool UAR_ActionBase::GetIsActive() const
{
	return bIsActive;
}

bool UAR_ActionBase::GetIsAutoStart() const
{
	return bIsAutoStart;
}

void UAR_ActionBase::SetIsAutoStart(const bool& Value)
{
	bIsAutoStart = Value;
}

UAR_ActionComponent* UAR_ActionBase::GetOwningComponent() const
{
	return Cast<UAR_ActionComponent>(GetOuter());
}

UWorld* UAR_ActionBase::GetWorld() const
{
	if (const UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp -> GetWorld();
	}
	
	return nullptr;
}
