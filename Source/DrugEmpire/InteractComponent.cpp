// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Player = Cast<ADrugEmpireCharacter>(GetOwner());

	InteractRange = 100.f;
}


// Called when the game starts
void UInteractComponent::BeginPlay(){
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *Player->GetName());

}

// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Player == nullptr) {
		return;
	}

	FHitResult HitResult;

	FVector StartVector = Player->FirstPersonCameraComponent->GetComponentLocation() + Player->FirstPersonCameraComponent->GetForwardVector();
	FVector EndVector = StartVector + (Player->FirstPersonCameraComponent->GetForwardVector() * InteractRange);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);

	//DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Blue, false, 1, 0, 1);

	bool GotHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, ECC_Visibility, CollisionParams);

	if (GotHit) {

		auto* Object = Cast<AInteractActorBase>(HitResult.GetActor());

		if (Object != nullptr) {
			SetInteractObject(Object);
			//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), Object);
		} else {
			SetInteractObject(nullptr);
		}

		return;

	}

	SetInteractObject(nullptr);
}

void UInteractComponent::Interact() {

	if (InteractActor == nullptr) { return; }

	if (GetOwner()->HasAuthority()) {
		InteractActor->Interact(Player);
	} else {
		ServerInteract(InteractActor, Player);
	}

}

void UInteractComponent::ServerInteract_Implementation(AInteractActorBase* Actor, ADrugEmpireCharacter* Caller) {

	Actor->Interact(Caller);

}

void UInteractComponent::SetInteractObject(AInteractActorBase* Object) {
	InteractActor = Object;
}

