// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBTTask_RangedAttack.h"
#include "AIController.h"
#include "AR_ProjectileMain.h"
#include "AR_StringLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UARBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

	if (ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController -> GetPawn());

		if (ensure(AIPawn))
		{
			const FVector MuzzleLoc = AIPawn -> GetMesh() -> GetSocketLocation(FSocketLibrary::MinionMuzzleSocket);
			const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent() -> GetValueAsObject(*FAIKeyLibrary::RMinionTargetActor));

			if (ensure(TargetActor))
			{
				FActorSpawnParameters ActorSpawnParameters;
				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ActorSpawnParameters.Owner = AIPawn;
				ActorSpawnParameters.Instigator = AIPawn;

				//const FVector Direction = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc, TargetActor -> GetActorLocation());
				const FRotator MuzzleRot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc, TargetActor -> GetActorLocation());
				const FTransform Transform = FTransform(MuzzleRot, MuzzleLoc);
				
				if (GetWorld() -> SpawnActor<AAR_ProjectileMain>(AAR_ProjectileMain::StaticClass(), Transform, ActorSpawnParameters))
				{
					return EBTNodeResult::Succeeded;
				}

				return EBTNodeResult::Failed;
			}

			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
