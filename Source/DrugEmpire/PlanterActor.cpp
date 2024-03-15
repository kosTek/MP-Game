// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanterActor.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "WeedDataAsset.h"

#include "Net/UnrealNetwork.h"

// Sets default values
APlanterActor::APlanterActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CurrentProgress = 0;
	RequiredProgress = 5;

	PlanterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planter Mesh"));
	RootComponent = PlanterMesh;

	SeedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seed Mesh"));
	SeedMesh->SetupAttachment(PlanterMesh);
	SeedMesh->SetIsReplicated(true);

	PlantedSeed = EWeedType::NONE;
	CurrentDataSet = nullptr;

	//PlantedSeed = EWeedType::WEED_OG;
}

void APlanterActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlanterActor, IsCompleted);
	DOREPLIFETIME(APlanterActor, RequiredProgress);
	DOREPLIFETIME(APlanterActor, CurrentProgress);
	DOREPLIFETIME(APlanterActor, PlanterType);
	DOREPLIFETIME(APlanterActor, PlantedSeed); 
	DOREPLIFETIME(APlanterActor, SeedMesh);

}

// Called when the game starts or when spawned
void APlanterActor::BeginPlay() {
	Super::BeginPlay();
	
	RequiredProgress = 10;

	GetWorld()->GetTimerManager().SetTimer(PlanterGrowingCycle, this, &APlanterActor::IncreaseProgress, 5.0f, true, 5.0f);

}

// Called every frame
void APlanterActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

bool APlanterActor::ServerIncreaseProgress_Validate(int Value) {

	if (IsCompleted) { return false; }

	return true;

}

void APlanterActor::ServerIncreaseProgress_Implementation(int Value) {

	if (CurrentProgress + Value >= RequiredProgress) {

		CurrentProgress = RequiredProgress;
		IsCompleted = true;
		SeedMesh->SetStaticMesh(CurrentDataSet->GrowProgressMeshList.Last());

	} else {
		if (CurrentDataSet != nullptr && GetPlantedSeed() != EWeedType::NONE) {

			CurrentProgress += Value;

			float Required = (float)RequiredProgress;

			int MeshToDisplay = 0;

			for (int i = 0; i < CurrentDataSet->GrowProgressMeshList.Num(); i++) {

				float StageRequirement = Required / ((float)CurrentDataSet->GrowProgressMeshList.Num() - i);

				UE_LOG(LogTemp, Warning, TEXT("Required: %f | Done: %i!"), StageRequirement, CurrentProgress);

				if (CurrentProgress > StageRequirement) {
					continue;
				}

				if (CurrentProgress < StageRequirement) {
					MeshToDisplay = i - 1;
					if (MeshToDisplay < 0) {
						MeshToDisplay = 0;
					}
					
					break;
				}

			}
			//UE_LOG(LogTemp, Warning, TEXT("Required Change!")); 
			SeedMesh->SetStaticMesh(CurrentDataSet->GrowProgressMeshList[MeshToDisplay]);

		}

	}
	 

	UE_LOG(LogTemp, Warning, TEXT("Current Progress is: %i out of %i!"), CurrentProgress, RequiredProgress);
}

void APlanterActor::ServerSetPlantedSeed_Implementation(EWeedType Type) {

	PlantedSeed = Type;

	if (PlantedSeed == EWeedType::NONE) {
		CurrentDataSet = nullptr;
		return;
	}

	for (int i = 0; i < WeedDataObjects.Num(); i++) {
		if (WeedDataObjects[i]->WeedType == PlantedSeed) {
			CurrentDataSet = WeedDataObjects[i];
			SeedMesh->SetStaticMesh(CurrentDataSet->GrowProgressMeshList[0]);
			break;
		}
	}

}

void APlanterActor::ServerInteract_Implementation(ADrugEmpireCharacter* Caller) {

	UE_LOG(LogTemp, Warning, TEXT("[Interact] %s - Server-side interaction"), *this->GetName());

	if (GetIsCompleted()) {

		UE_LOG(LogTemp, Warning, TEXT("[Interact] %s - Plant completed and collected!"), *this->GetName());

		// Add item to inventory logic here

		ServerSetPlantedSeed(EWeedType::NONE);
		CurrentProgress = 0;

	} else {
		// Planting logic and UI here

		ServerSetPlantedSeed(EWeedType::WEED_OG); // Debug

	}

	

}

void APlanterActor::IncreaseProgress() {

	// Create logic that checks the fertiliser, seed and plant pot type
	if (HasAuthority()) {

		ServerIncreaseProgress(1);

	}

}



