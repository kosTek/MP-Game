// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "ItemBase.generated.h"


UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class DRUGEMPIRE_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	virtual void OnUse();

	UFUNCTION(BlueprintCallable)
	virtual void OnDrop();

	UFUNCTION(BlueprintCallable)
	virtual void OnEquip();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Index = -1;

	UFUNCTION(BlueprintCallable)
	void SetIndex(int Value) { Index = Value; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int StackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxStackSize = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<EItemFlag> ItemFlags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ItemBuyValue{ 0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ItemSellValue{ 0 };

	/* Only works with consumable items that have "usable" item flag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int FoodValue{ 0 };

	/* Only works with consumable items that have "usable" item flag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int WaterValue{ 0 };

	/* Only works with consumable items that have "usable" item flag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int EnergyValue{ 0 };

};
