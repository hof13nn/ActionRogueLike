// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Action_ProjectileAttack.h"
#include "AR_StringLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

static TAutoConsoleVariable<bool> CVarDebugDrawProjectilePath(TEXT("su.ProjectilePathDebugDraw"), false, TEXT("Enable Debug Lines for Projectile Path}"), ECVF_Cheat);

UAR_Action_ProjectileAttack::UAR_Action_ProjectileAttack()
{
	AttackAnimDelay = 0.2f;
	PrimaryAttackAnim = nullptr;
}

void UAR_Action_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ACharacter* Char = Cast<ACharacter>(Instigator))
	{
		if (ensureMsgf(PrimaryAttackAnim, TEXT("UAR_Action_ProjectileAttack::StartAction_Implementation: %s: AttackAnim is NULL"), *GetNameSafe(this)))
		{
			Char -> PlayAnimMontage(PrimaryAttackAnim);

			if (UParticleSystem* Cast = LoadObject<UParticleSystem>(this, *FPathLibrary::ProjectileMainCastPath))
			{
				UGameplayStatics::SpawnEmitterAttached(Cast, Char -> GetMesh(), FSocketLibrary::CharacterProjectileSpawnSocket);

				FTimerHandle AttackDelay_TimerHandle;
				GetWorld() -> GetTimerManager().SetTimer(AttackDelay_TimerHandle, [&, Char] { AttackDelay_Elapsed(Char); }, AttackAnimDelay, false);
			}
		}
	}
}

void UAR_Action_ProjectileAttack::AttackDelay_Elapsed(ACharacter* Instigator)
{
	if (Instigator)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Owner = Instigator;
		SpawnParameters.Instigator = Instigator;
		
		const FVector SpawnLocation = Instigator -> GetMesh() -> GetSocketLocation(FSocketLibrary::CharacterProjectileSpawnSocket);
		const FRotator Rotation = CalculateRotation(Instigator, SpawnLocation);
		const FTransform Transform = FTransform(Rotation, SpawnLocation);

		if (GetWorld())
		{
			if (!GetWorld() -> SpawnActor<AActor>(ProjectileClass, Transform, SpawnParameters))
			{
				UE_LOG(LogTemp, Error, TEXT("AAR_Character::SpawnProjectile: Couldn't spawn Projectile"));
			}
		}

		StopAction(Instigator);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s::AttackDelay_Elapsed: Instigator is NULL"), *GetNameSafe(this));
	}
}

FRotator UAR_Action_ProjectileAttack::CalculateRotation(ACharacter* Instigator, const FVector& SpawnLocation) const
{
	if (GetWorld())
	{
		FHitResult HitResult;

		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		
		const FVector StartLocation = Instigator -> GetPawnViewLocation();
		const FVector EndLocation = StartLocation + (Instigator -> GetControlRotation().Vector() * 5000.f);
		
		const bool bIsHit = GetWorld() -> LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, QueryParams);

		if (CVarDebugDrawProjectilePath.GetValueOnGameThread())
		{
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, bIsHit ? FColor::Green : FColor::Red, false, 2.f, 0.f, 2.f);
		}

		return UKismetMathLibrary::FindLookAtRotation(SpawnLocation, bIsHit ? HitResult.Location : EndLocation);
	}

	return FRotator::ZeroRotator;
}