// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBTTask_RestoreHealth.h"

#include "AIController.h"
#include "AR_Damageable.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UARBTTask_RestoreHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

	if (ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController -> GetPawn());

		if (ensure(AIPawn))
		{
			IAR_Damageable::Execute_RestoreHealth(AIPawn);
			return EBTNodeResult::Succeeded;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
