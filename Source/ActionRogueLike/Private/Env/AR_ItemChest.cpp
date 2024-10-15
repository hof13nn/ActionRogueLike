// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_ItemChest.h"

#include "Components/BoxComponent.h"
#include "Engine/TimelineTemplate.h"


// Sets default values
AAR_ItemChest::AAR_ItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetupComponents();
	TargetPitch = 110.f;
}

void AAR_ItemChest::SetupComponents()
{
	if (!Root)
	{
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

		if (Root)
		{
			RootComponent = Root;
		}
	}
	
	if (!Mesh)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if (Mesh)
		{
			Mesh -> SetupAttachment(RootComponent);
		}
	}

	if (!LidMesh)
	{
		LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid Mesh"));

		if (LidMesh)
		{
			LidMesh -> SetupAttachment(Mesh);
		}
	}

	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (BoxComponent)
		{
			BoxComponent -> SetupAttachment(RootComponent);
		}
	}

	if (!TimelineTemplate)
	{
		TimelineTemplate = CreateDefaultSubobject<UTimelineComponent>(TEXT("DashTimeLine"));

		if (TimelineTemplate)
		{
			AddOwnedComponent(TimelineTemplate);
		}
	}
}

// Called when the game starts or when spawned
void AAR_ItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void AAR_ItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// if (LidMesh)
	// {
	// 	LidMesh -> SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
	//
	// 	TimelineTemplate -> Play();
	// 	
	// 	return true;
	// }
	//
	// return false;
}
