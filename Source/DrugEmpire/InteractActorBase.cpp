// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActorBase.h"
#include "DrugEmpireCharacter.h"

// Sets default values
AInteractActorBase::AInteractActorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractActorBase::Interact(ADrugEmpireCharacter* Caller) {

	ServerInteract(Caller);

}

// Called when the game starts or when spawned
void AInteractActorBase::BeginPlay(){
	Super::BeginPlay();
	
}

void AInteractActorBase::ServerInteract_Implementation(ADrugEmpireCharacter* Caller) {

	UE_LOG(LogTemp, Warning, TEXT("[Interact] %s - Server-side interaction"), *this->GetName());

}

void AInteractActorBase::ReplicateInteract_Implementation() {

	UE_LOG(LogTemp, Warning, TEXT("[Interact] %s - Replicated interaction"), *this->GetName());

}

// Called every frame
void AInteractActorBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

