// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AR_InteractionComponent.generated.h"


class AAR_Character;
class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UAR_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	UAR_InteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	// Called every frame
	void PrimaryInteract();

private:
	TWeakObjectPtr<AAR_Character> Owner;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere)
	float TraceLength;
};
