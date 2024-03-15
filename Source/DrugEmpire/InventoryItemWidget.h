// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class DRUGEMPIRE_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryItemWidget(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere)
	int Index;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* BorderImage;

	UFUNCTION(BlueprintCallable)
	void SetItemImage(UTexture2D* Texture);


};
