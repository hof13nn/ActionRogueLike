// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_AICharacter.h"

#include "AIController.h"
#include "AR_AttributeComponent.h"
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

	if (!AttributeComponent)
	{
		AttributeComponent = CreateDefaultSubobject<UAR_AttributeComponent>(TEXT("Attribute Component"));

		if (ensure(AttributeComponent))
		{
			AddOwnedComponent(AttributeComponent);
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

			DrawDebugString(GetWorld(), GetActorLocation(), TEXT("Player Spotted"), nullptr, FColor::Green, 2.f, true);
		}
	}
}

void AAR_AICharacter::DecreaseHealth_Implementation(const float& Amount)
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> DecreaseHealth(Amount);

		FString CurrentHealth = FString::Printf(TEXT("Health's been resored. Current Health: %f"), AttributeComponent -> GetCurrentHealth());
		
		DrawDebugString(GetWorld(), GetActorLocation(), CurrentHealth, nullptr, FColor::Green, 4.f, true);
	}
}

void AAR_AICharacter::IncreaseHealth_Implementation(const float& Amount)
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> IncreaseHealth(Amount);
	}
}

void AAR_AICharacter::RestoreHealth_Implementation()
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> RestoreHealth();

		FString CurrentHealth = FString::Printf(TEXT("Health's been resored. Current Health: %f"), AttributeComponent -> GetCurrentHealth());
		
		DrawDebugString(GetWorld(), GetActorLocation(), CurrentHealth, nullptr, FColor::Green, 4.f, true);
	}
}

bool AAR_AICharacter::GetIsLowHealth_Implementation()
{
	if (ensure(AttributeComponent))
	{
		return  AttributeComponent -> GetIsLowHealth();
	}

	return false;
}
