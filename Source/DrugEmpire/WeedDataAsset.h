// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enumerations.h"
#include "WeedDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DRUGEMPIRE_API UWeedDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeedType WeedType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeedName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* WeedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UStaticMesh*> GrowProgressMeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RequiredGrowthTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SeedPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SellPrice;

};
