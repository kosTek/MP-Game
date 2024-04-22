// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Image.h"

UInventoryItemWidget::UInventoryItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	Index = -1;

}

void UInventoryItemWidget::SetItemImage(UTexture2D* Texture) {

	ItemImage->SetBrushFromTexture(Texture);

}

void UInventoryItemWidget::ResetVisuals() {

	SetItemImage(DefaultTexture);

}
