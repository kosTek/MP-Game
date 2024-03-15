// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractActorBase.generated.h"

class ADrugEmpireCharacter;

UCLASS()
class DRUGEMPIRE_API AInteractActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActorBase();

	UFUNCTION(BlueprintCallable)
	virtual void Interact(ADrugEmpireCharacter* Caller);

	UFUNCTION(Server, Reliable)
	virtual void ServerInteract(ADrugEmpireCharacter* Caller);

	UFUNCTION(NetMulticast, Reliable)
	virtual void ReplicateInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ServerInteract_Implementation(ADrugEmpireCharacter* Caller);
	virtual void ReplicateInteract_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
