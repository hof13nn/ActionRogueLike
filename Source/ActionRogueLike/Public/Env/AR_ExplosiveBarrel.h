#pragma once

#include "CoreMinimal.h"
#include "AR_ExplosiveBarrel.generated.h"

class URadialForceComponent;
class UBoxComponent;

UCLASS()
class ACTIONROGUELIKE_API AAR_ExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	AAR_ExplosiveBarrel();

private:
	void SetupComponents();
	UFUNCTION()
	void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	virtual void BeginPlay() override;

public:

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	URadialForceComponent* RadialForceComponent;
};