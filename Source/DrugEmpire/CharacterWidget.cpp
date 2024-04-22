// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryItemWidget.h"
#include "DrugEmpireCharacter.h"
#include "InventoryComponent.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"


UCharacterWidget::UCharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UCharacterWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (InventoryItemSlot == nullptr) { return; }

	for (int i = 0; i < NumberOfInventoryRows; i++) {

		UHorizontalBox* HBox = NewObject<UHorizontalBox>(this);
		HBox->SetVisibility(ESlateVisibility::Visible);

		UVerticalBoxSlot* WidgetSlot = InventoryVertical->AddChildToVerticalBox(HBox);
		WidgetSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		WidgetSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			
		InventoryRows.Add(HBox);

	}

	int SlotIndex = 0;

	for (int i = 0; i < InventoryRows.Num(); i++) {

		for (int k = 0; k < NumberOfSlotsPerRow; k++) {
			UInventoryItemWidget* InventorySlot = Cast<UInventoryItemWidget>(CreateWidget(this, InventoryItemSlot));

			if (InventorySlot) {
				InventorySlot->Index = SlotIndex;
				InventorySlot->SetVisibility(ESlateVisibility::Visible);

				UHorizontalBoxSlot* HBoxSlot = InventoryRows[i]->AddChildToHorizontalBox(InventorySlot);

				HBoxSlot->SetPadding(FMargin(20, 20, 0, 0));
				HBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				HBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

				SlotIndex += 1;
			}

		}

	}

}

void UCharacterWidget::BindDelegate() {

	PlayerOwner = Cast<ADrugEmpireCharacter>(this->GetOwningPlayerPawn());

	PlayerOwner->InventoryComponent->OnInventoryUpdate.AddDynamic(this, &UCharacterWidget::RefreshInventory);

	//UE_LOG(LogTemp, Warning, TEXT("Number of items widget reads: %i"), PlayerOwner->InventoryComponent->GetPlayerItems().Num());
}

void UCharacterWidget::ClearInventoryVisuals() {

	//int NumberOfSlots = NumberOfInventoryRows * NumberOfSlotsPerRow;

	TArray<UWidget*> Children;

	for (int i = 0; i < InventoryRows.Num(); i++) {	

		Children = InventoryRows[i]->GetAllChildren();

	}

	for (int i = 0; i < Children.Num(); i++) {

		UInventoryItemWidget* ItemBox = Cast<UInventoryItemWidget>(Children[i]);

		if (!ItemBox) { continue; }

		ItemBox->ResetVisuals();

	}

}

void UCharacterWidget::RefreshInventory() {
	UE_LOG(LogTemp, Warning, TEXT("[Inventory] Update function called!"));

	//ClearInventoryVisuals();

}
