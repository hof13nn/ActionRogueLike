// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AICharacter.h"

#include "AIController.h"
#include "AR_StringLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AAR_AICharacter::AAR_AICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetupComponents();
}

void AAR_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ensure(PawnSensingComponent))
	{
		PawnSensingComponent -> OnSeePawn.AddDynamic(this, &ThisClass::OnSeePawn);
	}
}

void AAR_AICharacter::SetupComponents()
{
	if (!PawnSensingComponent)
	{
		PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

		if (ensure(PawnSensingComponent))
		{

			AddOwnedComponent(PawnSensingComponent);
		}
	}
}

void AAR_AICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if (ensure(AIController))
	{
		UBlackboardComponent* BlackboardComponent = AIController -> GetBlackboardComponent();

		if (ensure(BlackboardComponent))
		{
			BlackboardComponent -> SetValueAsObject(*FAIKeyLibrary::RMinionTargetActor, Pawn);

			DrawDebugString(GetWorld(), GetActorLocation(), TEXT("Player Spotted"), nullptr, FColor::Green, 4.f, true);
		}
	}
}