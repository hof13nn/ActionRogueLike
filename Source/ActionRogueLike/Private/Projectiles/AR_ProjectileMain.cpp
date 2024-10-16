// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ProjectileMain.h"
#include "AR_ActionComponent.h"
#include "AR_ActionEffect.h"
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

	Damage = 50.f;
	ProjectileSpeed = 2500.f;
	
	AAR_ProjectileMain::SetupComponents();
}


void AAR_ProjectileMain::SetupComponents()
{
	Super::SetupComponents();

	if (ensure(MovementComponent))
	{
		MovementComponent -> InitialSpeed = ProjectileSpeed;
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
	
	if (ensure(BoxComponent))
	{
		//BoxComponent -> OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
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
			AudioComponent -> Play();
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
	if (ensure(OtherActor) && OtherActor != GetInstigator())
	{
		UAR_ActionComponent* AC = Cast<UAR_ActionComponent>(OtherActor -> GetComponentByClass(UAR_ActionComponent::StaticClass()));

		if (AC && AC -> HasTag(ParryTag))
		{
			MovementComponent -> Velocity = -MovementComponent -> Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		
		if (OtherActor -> Implements<UAR_Damageable>())
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, GetOwner(), nullptr);

			if (AC)
			{
				if (const TSubclassOf<UAR_ActionEffect> Effect = LoadClass<UAR_ActionEffect>(this, TEXT("/Game/BPs/Actions/BP_Action_Effect_Burning_00.BP_Action_Effect_Burning_00_C")))
				{
					UE_LOG(LogTemp, Warning, TEXT("%s::OnOverlap: Adding Effect"), *GetNameSafe(this));
					AC -> AddAction(GetInstigator(), Effect);
				}
			}
			
			if (OverlappedComponent)
			{
				if (OverlappedComponent -> IsSimulatingPhysics(SweepResult.BoneName))
				{
					FVector Direction = SweepResult.TraceEnd - SweepResult.TraceStart;
					Direction.Normalize();
					OverlappedComponent -> AddImpulseAtLocation(Direction * 300000.f, SweepResult.ImpactPoint, SweepResult.BoneName);
				}
			}

			if (TSubclassOf<UCameraShakeBase> CameraShakeBase = LoadClass<UCameraShakeBase>(this, *FPathLibrary::ProjectileMainCameraShakePath))
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeBase, GetActorLocation(), 0.f, 800.f);
				//DrawDebugSphere(GetWorld(), GetActorLocation(), 800.f, 15, FColor::Red, true, 3.f);
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