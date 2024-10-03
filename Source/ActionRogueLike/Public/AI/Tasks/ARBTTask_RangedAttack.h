// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ARBTTask_RangedAttack.generated.h"

class AAR_ProjectileBase;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UARBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UARBTTask_RangedAttack();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category= AI)
	TSubclassOf<AAR_ProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, Category= AI)
	float MaxProjectileSpreadPitch;
	UPROPERTY(EditAnywhere, Category= AI)
	float MaxProjectileSpreadYaw;
};
