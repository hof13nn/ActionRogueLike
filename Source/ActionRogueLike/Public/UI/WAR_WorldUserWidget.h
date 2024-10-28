// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WAR_WorldUserWidget.generated.h"

class UAR_AttributeComponent;
class USizeBox;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UWAR_WorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAttachedToActor(AActor* OwningActor);
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = UI, meta=(AllowPrivateAccess = true, ExposeOnSpawn = true))
	AActor* AttachedToActor;
	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;
};
