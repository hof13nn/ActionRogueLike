// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileSpecial.h"

#include "AR_StringLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AAR_ProjectileSpecial::AAR_ProjectileSpecial()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AActor::SetLifeSpan(5.f);
	AAR_ProjectileSpecial::SetupComponents();
}

void AAR_ProjectileSpecial::BeginPlay()
{
	Super::BeginPlay();

	// if (GetWorld())
	// {
	// 	GetWorld() -> GetTimerManager().SetTimer(ImpulseTimerHandle, [&]{ RadialForceComponent -> FireImpulse(); }, .25f, true);
	// }
}

void AAR_ProjectileSpecial::BeginDestroy()
{
	Super::BeginDestroy();
	
	// if (GetWorld())
	// {
	// 	GetWorld() -> GetTimerManager().ClearTimer(ImpulseTimerHandle);
	// }
}

void AAR_ProjectileSpecial::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (BoxComponent)
	{
		BoxComponent -> SetBoxExtent(FVector(35.f));
		BoxComponent -> OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	}

	if (ParticleSystem)
	{
		if (UParticleSystem* Particle = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileSpecialPath))
		{
			ParticleSystem -> SetTemplate(Particle);
		}
	}
}

void AAR_ProjectileSpecial::SetupComponents()
{
	Super::SetupComponents();

	if (MovementComponent)
	{
		MovementComponent -> InitialSpeed = 1000.f;
	}
	
	if (!RadialForceComponent)
	{
		RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));

		if (RadialForceComponent)
		{
			RadialForceComponent -> Radius = 650.f;
			RadialForceComponent -> Falloff = RIF_Constant;
			RadialForceComponent -> ImpulseStrength = 1000.f;
			RadialForceComponent -> ForceStrength = -25000.f;
			RadialForceComponent -> bImpulseVelChange = true;
			RadialForceComponent -> SetAutoActivate(true);
			RadialForceComponent -> AddCollisionChannelToAffect(ECC_WorldDynamic);
			RadialForceComponent -> RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
			RadialForceComponent -> SetupAttachment(RootComponent);
		}
	}
}

void AAR_ProjectileSpecial::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		OtherActor -> Destroy();
	}
}
