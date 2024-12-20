﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "AR_ActionComponent.generated.h"

class UAR_ActionBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UAR_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAR_ActionComponent();

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(AActor* Instigator, TSubclassOf<UAR_ActionBase> ActionClass);
	void RemoveAction(UAR_ActionBase* Action);
	UAR_ActionBase* GetAction(TSubclassOf<UAR_ActionBase> ActionClass);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, const FName& ActionName);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, const FName& ActionName);
	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddTags(const FGameplayTagContainer& Tags);
	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddTag(const FGameplayTag& Tag);
	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveTags(const FGameplayTagContainer& Tags);
	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveTag(const FGameplayTag& Tag);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool HasTags(const FGameplayTagContainer& Tags);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool HasTag(const FGameplayTag& Tag);
	// UFUNCTION(BlueprintCallable, Category="Actions")
	// FGameplayTagContainer& GetActiveGameplayTags();
	
protected:
	virtual void OnRegister() override;

	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, const FName& ActionName);
private:
	UPROPERTY()
	TArray<UAR_ActionBase*> ActionsArr;
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UAR_ActionBase>> ActionClassesArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer ActiveGameplayTags;
};
