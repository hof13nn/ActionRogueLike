// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBTService_CheckHealth.h"

#include "AIController.h"
#include "AR_Damageable.h"
#include "BehaviorTree/BlackboardComponent.h"

void UARBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComponent))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();

		if (ensure(AIController))
		{
			APawn* AIPawn = AIController -> GetPawn();

			if (ensure(AIPawn))
			{
				FString Value = IAR_Damageable::Execute_GetIsLowHealth(AIPawn) ? TEXT("True") : TEXT("False");
				
				BlackboardComponent -> SetValueAsBool(LowHealthKey.SelectedKeyName, IAR_Damageable::Execute_GetIsLowHealth(AIPawn));
			}
		}
	}
}
