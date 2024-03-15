// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/* Type of planter that the object is, based on the type the growing speed and capacity will differ */
UENUM(BlueprintType)
enum class EPlanterType : uint8 {
	NONE			UMETA(DisplayName = "NONE"),
	FLOWER_POT		UMETA(DisplayName = "Flower Pot"),
};

UENUM(BlueprintType)
enum class EWeedType : uint8 {
	NONE			UMETA(DisplayName = "NONE"),	
	WEED_OG			UMETA(DisplayName = "OG Weed"),
};

UENUM(BlueprintType)
enum class EItemType : uint8 {
	MONEY			UMETA(DisplayName = "Money"),
	WEED_OG			UMETA(DisplayName = "OG Weed"),
	WEED_AK			UMETA(DisplayName = "AK Weed"),
};

UENUM(BlueprintType)
enum class EItemFlag : uint8 {
	WEAPON			UMETA(DisplayName = "Weapon"),
	CLOTHING		UMETA(DisplayName = "Clothing"),
	USABLE			UMETA(DisplayName = "Usable"),
	CANT_DROP		UMETA(DisplayName = "Can't Drop"),
	QUEST_ITEM      UMETA(DisplayName = "Quest Item"),
	MONEY			UMETA(DisplayName = "Money"),
	STACKABLE		UMETA(DisplayName = "Stackable"),
	CANT_SELL		UMETA(DisplayName = "Can't Sell"),
};
