// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

class UInventoryItemWidget;
class ADrugEmpireCharacter;

class UTextBlock;
class UImage;
class UTexture2D;
class UHorizontalBox;
class UVerticalBox;

UCLASS()
class DRUGEMPIRE_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

	UCharacterWidget(const FObjectInitializer& ObjectInitializer);
	
public:

	virtual void NativeConstruct() override;

	/* Sets Owner of the widget which is required to read inventory information */
	void BindDelegate();

	ADrugEmpireCharacter* GetOwner() { return PlayerOwner; }

	/* How many rows will the inventory have */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfInventoryRows{ 5 };

	/* How many columns will the inventory have */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfSlotsPerRow{ 4 };

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryItemWidget> InventoryItemSlot;

	/* Called upon creation and if the inventory status changes. Updates the visual elements in the inventory panel */
	UFUNCTION()
	void RefreshInventory();

protected:

	/* Brings the inventory visuals to a default state */
	void ClearInventoryVisuals();

private:

	UPROPERTY()
	ADrugEmpireCharacter* PlayerOwner;

	/* Vertical box that contains rows for inventrory slots */
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* InventoryVertical;

	/* Contains created inventory wigets in order */
	TArray<UInventoryItemWidget*> InventorySlots;

	/* Contains horizontal rows for inventory slots to be placed in */
	TArray<UHorizontalBox*> InventoryRows;

};
