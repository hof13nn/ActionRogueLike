// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_InteractableObjectBase.h"

#include "Components/BoxComponent.h"


// Sets default values
AAR_InteractableObjectBase::AAR_InteractableObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

void AAR_InteractableObjectBase::SetupComponents()
{
	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (ensure(BoxComponent))
		{
			RootComponent = BoxComponent;
		}
	}

	if (!Mesh)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

		if (ensure(Mesh))
		{
			Mesh -> SetupAttachment(RootComponent);
		}
	}
}

void AAR_InteractableObjectBase::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

