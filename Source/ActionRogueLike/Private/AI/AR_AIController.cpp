// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AIController.h"
#include "AR_StringLibrary.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"


// Sets default values
AAR_AIController::AAR_AIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BehaviorTree = nullptr;
}



void AAR_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BehaviorTree = LoadObject<UBehaviorTree>(this, *FPathLibrary::RMinionBTPath);

	if (ensureMsgf(BehaviorTree, TEXT("AAR_AIController::OnPossess: BT is NULL! Provide a valid path")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AAR_AIController::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Error, TEXT("AAR_AIController::OnPossess: 2"));
	//
	// if (AActor* PlayerPawn = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0)))
	// {
	// 	GetBlackboardComponent() -> SetValueAsVector(*FAIKeyLibrary::RMinionMoveToLoc, PlayerPawn -> GetActorLocation());
	// 	GetBlackboardComponent() -> SetValueAsObject(*FAIKeyLibrary::RMinionTargetActor, PlayerPawn);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("AAR_AIController::OnPossess: No Player found"));
	// }
}
