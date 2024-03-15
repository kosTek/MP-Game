// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActorBase.h"
#include "ItemPickupActor.generated.h"

class UStaticMeshComponent;
class UItemBase;

UCLASS()
class DRUGEMPIRE_API AItemPickupActor : public AInteractActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickupActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemBase* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ServerInteract_Implementation(ADrugEmpireCharacter* Caller) override;

};
