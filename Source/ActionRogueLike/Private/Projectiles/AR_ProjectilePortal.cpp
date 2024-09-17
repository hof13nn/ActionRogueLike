// Fill out your copyright notice in the Description page of Project Settings.

#include "AR_ProjectilePortal.h"
#include "AR_StringLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AAR_ProjectilePortal::AAR_ProjectilePortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AAR_ProjectilePortal::SetupComponents();
}

// Called when the game starts or when spawned
void AAR_ProjectilePortal::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorld() -> GetTimerManager().SetTimer(LifespanTimerHandle, this, &ThisClass::ScheduleTeleportTimer, 0.2f);
	}
}

void AAR_ProjectilePortal::SetupComponents()
{
	Super::SetupComponents();

	if (MovementComponent)
	{
		MovementComponent -> InitialSpeed = 1500.f;
	}
}

void AAR_ProjectilePortal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxComponent)
	{
		BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	}

	if (ParticleSystem)
	{
		if (UParticleSystem* Particle = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileTeleportPath))
		{
			ParticleSystem -> SetTemplate(Particle);
		}
	}
	
	if (!Explosion)
	{
		if (UParticleSystem* ParticleEmitter = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileTeleportExplosionPath))
		{
			Explosion = ParticleEmitter;
		}
	}
}

void AAR_ProjectilePortal::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	ScheduleTeleportTimer();
}


void AAR_ProjectilePortal::ScheduleTeleportTimer()
{
	if (Explosion)
	{
		if (UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation()))
		{
			if (MovementComponent)
			{
				MovementComponent -> StopMovementImmediately();

				if (GetWorld())
				{
					GetWorld() -> GetTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::Teleport, 0.3f);
				}
			}
		}
	}
}

void AAR_ProjectilePortal::Teleport()
{
	if (GetOwner())
	{
		GetOwner() -> SetActorLocation(GetActorLocation());
		Destroy();
	}
}
