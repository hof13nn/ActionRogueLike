// Fill out your copyright notice in the Description page of Project Settings.

#include "WAR_WorldUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void UWAR_WorldUserWidget::SetAttachedToActor(AActor* OwningActor)
{
	if (OwningActor)
	{
		AttachedToActor = OwningActor;
	}
}

void UWAR_WorldUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWAR_WorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (ensureMsgf(AttachedToActor, TEXT("UWAR_WorldUserWidget::NativeTick: AttachedToActor is NULL")))
	{
		FVector2D ScreenPosition;
		
		if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedToActor -> GetActorLocation(), ScreenPosition))
		{
			float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

			ScreenPosition /= Scale;

			if (ParentSizeBox)
			{
				ParentSizeBox -> SetRenderTranslation(ScreenPosition);
			}
		}
	}
}
