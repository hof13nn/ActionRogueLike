// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AR_AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, Instigator, UAR_AttributeComponent*, Component, float, NewValue, float, HealthDelta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UAR_AttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAR_AttributeComponent();

	UFUNCTION(BlueprintCallable)
	bool DecreaseHealth(AActor* InstigatorActor, const float& Amount);
	void IncreaseHealth(const float& Amount);
	UFUNCTION(BlueprintCallable)
	bool DecreaseRage(AActor* InstigatorActor, const float& Amount);
	void IncreaseRage(const float& Amount);
	void RestoreHealth();
	UFUNCTION(BlueprintCallable)
	bool GetNeedHealth();
	UFUNCTION(BlueprintCallable)
	bool GetIsLowHealth();
	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() const;
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	float GetCurrentRage();
	UFUNCTION(BlueprintCallable)
	float GetMaxRage();
	UFUNCTION(BlueprintCallable)
	bool GetIsEnoughRage(float RageCost);
	UFUNCTION(BlueprintCallable)
	static UAR_AttributeComponent* GetAttributeComponent(AActor* TargetActor);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor* Instigator, float NewValue, float HealthDelta);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRageChanged(AActor* Instigator, float NewValue, float HealthDelta);
	
private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category= "Attributes")
	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category= "Attributes")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category= "Attributes")
	float CurrentRage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category= "Attributes")
	float MaxRage;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnRageChanged;
};
