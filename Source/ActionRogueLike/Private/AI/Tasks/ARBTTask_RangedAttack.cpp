// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBTTask_RangedAttack.h"
#include "AIController.h"
#include "AR_Damageable.h"
#include "AR_ProjectileMain.h"
#include "AR_StringLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UARBTTask_RangedAttack::UARBTTask_RangedAttack()
{
	MaxProjectileSpreadPitch = 2.f;
	MaxProjectileSpreadYaw = 2.f;
}

EBTNodeResult::Type UARBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

	if (ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController -> GetPawn());

		if (ensure(AIPawn))
		{
			const FVector MuzzleLoc = AIPawn -> GetMesh() -> GetSocketLocation(FSocketLibrary::MinionMuzzleSocket);
			AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent() -> GetValueAsObject(*FAIKeyLibrary::RMinionTargetActor));

			if (TargetActor && IAR_Damageable::Execute_GetIsAlive(TargetActor))
			{
				FActorSpawnParameters ActorSpawnParameters;
				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ActorSpawnParameters.Owner = AIPawn;
				ActorSpawnParameters.Instigator = AIPawn;

				//const FVector Direction = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc, TargetActor -> GetActorLocation());
				FRotator MuzzleRot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc, TargetActor -> GetActorLocation());
				MuzzleRot.Pitch += FMath::RandRange(0.f, MaxProjectileSpreadPitch);
				MuzzleRot.Yaw += FMath::RandRange(-MaxProjectileSpreadYaw, MaxProjectileSpreadYaw);
				const FTransform Transform = FTransform(MuzzleRot, MuzzleLoc);

				if (ensureMsgf(ProjectileClass, TEXT("UARBTTask_RangedAttack::ExecuteTask: ProjectileClass is NULL")))
				{
					if (GetWorld() -> SpawnActor<AActor>(ProjectileClass, Transform, ActorSpawnParameters))
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

	return EBTNodeResult::Failed;
}
