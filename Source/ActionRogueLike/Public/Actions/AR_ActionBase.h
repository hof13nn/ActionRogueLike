// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AR_ActionBase.generated.h"

class UAR_ActionComponent;

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UAR_ActionBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);
	UFUNCTION(BlueprintCallable, Category="Action")
	FName GetActionName() const;
	UFUNCTION(BlueprintCallable, Category="Action")
	bool GetIsActive() const;
	UFUNCTION(BlueprintCallable, Category="Action")
	bool GetIsAutoStart() const;
	UFUNCTION(BlueprintCallable, Category="Action")
	void SetIsAutoStart(const bool& Value);
	UFUNCTION(BlueprintCallable, Category="Action")
	UAR_ActionComponent* GetOwningComponent() const;
	UFUNCTION(BlueprintCallable, Category="Action")
	virtual UWorld* GetWorld() const override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	FName Name;
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	bool bIsActive;

protected:
	UPROPERTY(VisibleAnywhere, Category="Action", meta=(AllowPrivateAccess="true"))
	bool bIsAutoStart;
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockedTags;
};
