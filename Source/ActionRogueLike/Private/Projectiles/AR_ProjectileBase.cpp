// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileBase.h"
#include "AR_StringLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AAR_ProjectileBase::AAR_ProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CachedLaunchPosition = FVector::ZeroVector;
	Tags.Emplace(FTagLibrary::ProjectileTag);
	
	SetupComponents();
}

void AAR_ProjectileBase::SetupComponents()
{
	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (BoxComponent)
		{
			BoxComponent -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			BoxComponent -> SetSimulatePhysics(false);
			BoxComponent -> SetEnableGravity(false);
			BoxComponent -> SetNotifyRigidBodyCollision(true);
			BoxComponent -> SetGenerateOverlapEvents(false);
			BoxComponent -> SetCollisionProfileName(FCollisionProfileLibrary::ProjectileProfile);
			BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::HandleHit);
			RootComponent = BoxComponent;
		}
	}

	if (!MovementComponent)
	{
		MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));

		if (MovementComponent)
		{
			MovementComponent -> InitialSpeed = 1000.f;
			MovementComponent -> bRotationFollowsVelocity = true;
			MovementComponent -> bInitialVelocityInLocalSpace = true;
			MovementComponent -> ProjectileGravityScale = 0.f;
		}
	}

	if (!ParticleSystem)
	{
		ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
		
		if (ParticleSystem)
		{
			if (UParticleSystem* Particle = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectilePath))
			{
				ParticleSystem -> SetTemplate(Particle);
				ParticleSystem -> SetupAttachment(RootComponent);
			}
		}
	}

	if (!Explosion)
	{
		if (UParticleSystem* ParticleEmitter = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileExplosionPath))
		{
			Explosion = ParticleEmitter;
		}
	}
}

// Called when the game starts or when spawned
void AAR_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	CachedLaunchPosition = GetActorLocation();
}

void AAR_ProjectileBase::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Explosion)
	{
		if (UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation()))
		{
			UE_LOG(LogTemp, Warning, TEXT("AAR_ProjectileBase::HandleHit: Destroy"));
			Destroy();
		}
	}
}
