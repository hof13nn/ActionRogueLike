// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_TargetDummy.h"

#include "AR_AttributeComponent.h"


// Sets default values
AAR_TargetDummy::AAR_TargetDummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetupComponents();
}

// Called when the game starts or when spawned
void AAR_TargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAR_TargetDummy::SetupComponents()
{
	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

		if (ensure(StaticMeshComponent))
		{
			RootComponent = StaticMeshComponent;
		}
	}

	if (!AttributeComponent)
	{
		AttributeComponent = CreateDefaultSubobject<UAR_AttributeComponent>(TEXT("Attribute Component"));

		if (ensure(AttributeComponent))
		{
			AttributeComponent -> OnHealthChanged.AddDynamic(this, &ThisClass::OnDecreaseHealth);
			AddOwnedComponent(AttributeComponent);
		}
	}
}

void AAR_TargetDummy::OnDecreaseHealth(TWeakObjectPtr<AActor> InstigatorActor, TWeakObjectPtr<UAR_AttributeComponent> Component,
                                       float NewValue, float HealthDelta)
{
	if(ensure(StaticMeshComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AAR_TargetDummy::OnDecreaseHealth"));
		StaticMeshComponent -> SetScalarParameterValueOnMaterials("TimeToHit", GetWorld() -> GetTimeSeconds());
	}
}

void AAR_TargetDummy::DecreaseHealth_Implementation(const float& Amount)
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent -> DecreaseHealth(Amount);
	}
}

