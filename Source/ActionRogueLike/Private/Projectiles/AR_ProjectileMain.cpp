// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileMain.h"
#include "AR_StringLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AAR_ProjectileMain::AAR_ProjectileMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AAR_ProjectileMain::SetupComponents();
}


void AAR_ProjectileMain::SetupComponents()
{
	Super::SetupComponents();

	if (MovementComponent)
	{
		MovementComponent -> InitialSpeed = 1000.f;
	}
}

// Called when the game starts or when spawned
void AAR_ProjectileMain::BeginPlay()
{
	Super::BeginPlay();
}

void AAR_ProjectileMain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (BoxComponent)
	{
		BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	}

	if (ParticleSystem)
	{
		if (UParticleSystem* Particle = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileMainPath))
		{
			ParticleSystem -> SetTemplate(Particle);
		}
	}
	
	if (!Explosion)
	{
		if (UParticleSystem* ParticleEmitter = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileMainExplosionPath))
		{
			Explosion = ParticleEmitter;
		}
	}
}


void AAR_ProjectileMain::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Explosion)
	{
		if (UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation()))
		{
			Destroy();
		}
	}
}
