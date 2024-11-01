// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AR_ActionBase.h"
#include "AR_Action_ProjectileAttack.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UAR_Action_ProjectileAttack : public UAR_ActionBase
{
	GENERATED_BODY()

public:
	UAR_Action_ProjectileAttack();
	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* Instigator);
	FRotator CalculateRotation(ACharacter* Instigator, const FVector& SpawnLocation) const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Attack", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category="Attack", meta=(AllowPrivateAccess="true"))
	float AttackAnimDelay;
	UPROPERTY(EditDefaultsOnly, Category="Attack", meta=(AllowPrivateAccess="true"))
	UAnimMontage* PrimaryAttackAnim;
};
