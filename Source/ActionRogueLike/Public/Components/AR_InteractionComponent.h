// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AR_InteractionComponent.generated.h"


class UWAR_WorldUserWidget;
class AAR_Character;
class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UAR_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	UAR_InteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindBestInteract();
	
	UFUNCTION(Server, Unreliable)
	void ServerInteract(AActor* InFocus);
public:
	// Called every frame
	void PrimaryInteract();

private:
	TWeakObjectPtr<AAR_Character> Owner;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere, Category= Trace)
	float TraceLength;
	UPROPERTY(EditAnywhere, Category= Trace)
	float TraceRadius;
	UPROPERTY(VisibleAnywhere, Category= Trace)
	AActor* FocusedActor;
	UPROPERTY(EditAnywhere, Category= Trace)
	TEnumAsByte<ECollisionChannel> QueryChannel;
	
	UPROPERTY(EditDefaultsOnly, Category= UI)
	TSubclassOf<UWAR_WorldUserWidget> DefaultWidgetClass;
	UPROPERTY()
	UWAR_WorldUserWidget* DefaultWidget;
};
