// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileBase.h"
#include "AR_StringLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AAR_ProjectileBase::AAR_ProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CachedLaunchPosition = FVector::ZeroVector;
	Tags.Emplace(FTagLibrary::ProjectileTag);

	AAR_ProjectileBase::SetupComponents();
}

void AAR_ProjectileBase::SetupComponents()
{
	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (ensure(BoxComponent))
		{
			BoxComponent -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			BoxComponent -> SetSimulatePhysics(false);
			BoxComponent -> SetEnableGravity(false);
			BoxComponent -> SetNotifyRigidBodyCollision(true);
			BoxComponent -> SetGenerateOverlapEvents(true);
			BoxComponent -> SetCollisionProfileName(FCollisionProfileLibrary::ProjectileProfile);
			RootComponent = BoxComponent;
		}
	}

	if (!MovementComponent)
	{
		MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));

		if (ensure(MovementComponent))
		{
			MovementComponent -> bRotationFollowsVelocity = true;
			MovementComponent -> bInitialVelocityInLocalSpace = true;
			MovementComponent -> ProjectileGravityScale = 0.f;
		}
	}

	if (!ParticleSystem)
	{
		ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));

		if (ensure(ParticleSystem))
		{
			ParticleSystem -> SetupAttachment(RootComponent);
		}
	}

	if (!AudioComponent)
	{
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

		if (ensure(AudioComponent))
		{
			AudioComponent -> SetAutoActivate(true);
			AddOwnedComponent(AudioComponent);
		}
	}
}

void AAR_ProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAR_ProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AAR_ProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
