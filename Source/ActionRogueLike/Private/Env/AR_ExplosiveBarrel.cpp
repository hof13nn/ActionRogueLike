// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ExplosiveBarrel.h"

#include "AR_StringLibrary.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AAR_ExplosiveBarrel::AAR_ExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetupComponents();
}

void AAR_ExplosiveBarrel::SetupComponents()
{
	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

		if (StaticMeshComponent)
		{
			StaticMeshComponent -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
			RootComponent = StaticMeshComponent;
		}
	}

	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (BoxComponent)
		{
			BoxComponent -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			BoxComponent -> SetCollisionProfileName(TEXT("World Static"));
			BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::HandleHit);
			BoxComponent -> SetupAttachment(RootComponent);
		}
	}

	if (!RadialForceComponent)
	{
		RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));

		if (RadialForceComponent)
		{
			RadialForceComponent -> Radius = 700.f;
			RadialForceComponent -> Falloff = RIF_Constant;
			RadialForceComponent -> ImpulseStrength = 2000.f;
			RadialForceComponent -> bImpulseVelChange = true;
			RadialForceComponent -> SetupAttachment(RootComponent);
		}
	}
}

// Called when the game starts or when spawned
void AAR_ExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAR_ExplosiveBarrel::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor -> ActorHasTag(FTagLibrary::ProjectileTag))
	{
		if (RadialForceComponent)
		{
			RadialForceComponent -> FireImpulse();
		}
	}
}