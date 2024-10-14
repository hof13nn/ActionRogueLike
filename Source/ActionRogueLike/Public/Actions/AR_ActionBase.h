// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AR_ActionBase.generated.h"

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UAR_ActionBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);
	UFUNCTION(BlueprintCallable, Category="Action")
	FName GetActionName() const;
	UFUNCTION(BlueprintCallable, Category="Action")
	UWorld* GetWorld() const override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	FName Name;
};
