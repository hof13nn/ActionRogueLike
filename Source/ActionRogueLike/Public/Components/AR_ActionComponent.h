// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void AddAction(TSubclassOf<UAR_ActionBase> ActionClass);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, const FName& ActionName);
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, const FName& ActionName);

protected:
	virtual void OnRegister() override;
	
private:
	UPROPERTY()
	TArray<UAR_ActionBase*> ActionsArr;
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UAR_ActionBase>> ActionClassesArr;
};
