// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileMain.h"
#include "AR_Damageable.h"
#include "AR_StringLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
AAR_ProjectileMain::AAR_ProjectileMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AAR_ProjectileMain::SetupComponents();

	Damage = 10.f;
}


void AAR_ProjectileMain::SetupComponents()
{
	Super::SetupComponents();

	if (ensure(MovementComponent))
	{
		MovementComponent -> InitialSpeed = 1000.f;
	}
}

// Called when the game starts or when spawned
void AAR_ProjectileMain::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(AudioComponent))
	{
		AudioComponent -> Play();
	}
}

void AAR_ProjectileMain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (ensure(BoxComponent))
	{
		BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
		BoxComponent -> OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	}

	if (ensure(ParticleSystem))
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

	if (ensure(AudioComponent))
	{
		if (USoundCue* Sound = LoadObject<USoundCue>(this, *FPathLibrary::ProjectileMainSoundPath))
		{
			AudioComponent -> SetSound(Sound);
		}
	}

	if (!HitSound)
	{
		if (USoundCue* Hit = LoadObject<USoundCue>(this, *FPathLibrary::ProjectileMainHitSoundPath))
		{
			HitSound = Hit;
		}
	}
}


void AAR_ProjectileMain::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ensure(OtherActor) && OtherActor != GetOwner())
	{
		if (OtherActor -> Implements<UAR_Damageable>())
		{
			IAR_Damageable::Execute_DecreaseHealth(OtherActor, Damage);
		}
		
		if (ensure(Explosion))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
		}

		if(ensure(HitSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
		}
			
		Destroy();
	}
}

void AAR_ProjectileMain::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensure(OtherActor) && OtherActor != GetOwner())
	{
		if (OtherActor -> Implements<UAR_Damageable>())
		{
			IAR_Damageable::Execute_DecreaseHealth(OtherActor, Damage);

			if (TSubclassOf<UCameraShakeBase> CameraShakeBase = LoadClass<UCameraShakeBase>(this, *FPathLibrary::ProjectileMainCameraShakePath))
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeBase, GetActorLocation(), 0.f, 800.f);
				DrawDebugSphere(GetWorld(), GetActorLocation(), 800.f, 15, FColor::Red, true, 3.f);
			}
		}
		
		if (ensure(Explosion))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
		}

		if(ensure(HitSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
		}
			
		Destroy();
	}
}