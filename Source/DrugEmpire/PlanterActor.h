// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActorBase.h"
#include "Enumerations.h"

#include "PlanterActor.generated.h"

UCLASS()
class DRUGEMPIRE_API APlanterActor : public AInteractActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanterActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Visual */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PlanterMesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SeedMesh;

	/* Data */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UWeedDataAsset*> WeedDataObjects;

	/* Interact */

	//virtual void ServerInteract() override;

	/* Planter Progress */

	UPROPERTY()
	FTimerHandle PlanterGrowingCycle;

	UPROPERTY(Replicated)
	bool IsCompleted;

	UPROPERTY(Replicated)
	int RequiredProgress;

	UPROPERTY(Replicated)
	int CurrentProgress;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseProgress(int Value);

	/*UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRequiredProgress(int Value);*/

	UFUNCTION(BlueprintCallable)
	int GetCurrentProgress() { return CurrentProgress; }

	UFUNCTION(BlueprintCallable)
	int GetRequiredProgress() { return RequiredProgress; }

	/* Types */

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	EPlanterType PlanterType;

	UPROPERTY(Replicated)
	EWeedType PlantedSeed;

	/* Set the type of the flower pot, it will have varying properties depending on the type of the pot */
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetPlanterType(EPlanterType Type);

	/* Set the seed that is meant to grow in the planter */
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetPlantedSeed(EWeedType Type);

	UFUNCTION(BlueprintCallable)
	EPlanterType GetPlanterType() { return PlanterType; }

	UFUNCTION(BlueprintCallable)
	EWeedType GetPlantedSeed() { return PlantedSeed; }

	UFUNCTION(BlueprintCallable)
	bool GetIsCompleted() { return IsCompleted; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void IncreaseProgress();

	bool ServerIncreaseProgress_Validate(int Value);
	void ServerIncreaseProgress_Implementation(int Value);

	void ServerSetPlanterType_Implementation(EPlanterType Type) { PlanterType = Type; }
	void ServerSetPlantedSeed_Implementation(EWeedType Type);

	/* Interact */

	virtual void ServerInteract_Implementation(ADrugEmpireCharacter* Caller) override;

private:	
	class UWeedDataAsset* CurrentDataSet;

};
