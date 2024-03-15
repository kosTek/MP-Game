// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickupActor.h"
#include "Components/StaticMeshComponent.h"
#include "DrugEmpireCharacter.h"
#include "InventoryComponent.h"

// Sets default values
AItemPickupActor::AItemPickupActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	SetReplicates(true);

}

// Called when the game starts or when spawned
void AItemPickupActor::BeginPlay(){

	Super::BeginPlay();
	
}

void AItemPickupActor::ServerInteract_Implementation(ADrugEmpireCharacter* Caller) {

	if (ItemData != nullptr) {
		Caller->InventoryComponent->AddPickupItem(this);
	} else {
		this->Destroy();
	}

}