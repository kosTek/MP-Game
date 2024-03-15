// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrugEmpireCharacter.h"
#include "InteractActorBase.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRUGEMPIRE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Range of player's ability to interact with objects. 
	Higher value means the player can interact with objects further away. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float InteractRange;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(Server, Reliable)
	void ServerInteract(AInteractActorBase* Actor, ADrugEmpireCharacter* Caller);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ServerInteract_Implementation(AInteractActorBase* Actor, ADrugEmpireCharacter* Caller);

private:	
	
	ADrugEmpireCharacter* Player;
	
	AInteractActorBase* InteractActor;

	void SetInteractObject(AInteractActorBase* Object);
};
