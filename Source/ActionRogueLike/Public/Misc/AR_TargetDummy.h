// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_Damageable.h"
#include "GameFramework/Actor.h"
#include "AR_TargetDummy.generated.h"

class UAR_AttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_TargetDummy : public AActor, public IAR_Damageable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAR_TargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetupComponents();
	UFUNCTION()
	void OnDecreaseHealth(TWeakObjectPtr<AActor> InstigatorActor, TWeakObjectPtr<UAR_AttributeComponent> Component, float NewValue, float HealthDelta);
	void DecreaseHealth_Implementation(const float& Amount) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UAR_AttributeComponent* AttributeComponent;
};
