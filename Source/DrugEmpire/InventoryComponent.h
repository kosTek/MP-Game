// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemBase;
class AItemPickupActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRUGEMPIRE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxInventoryItems;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerAddItem(UItemBase* Item);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerAddPickupItem(AItemPickupActor* Item);

	UFUNCTION(BlueprintCallable)
	void AddPickupItem(AItemPickupActor* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerRemoveItem(UItemBase* Item);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerRemoveItemByIndex(int Index);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerChangeItemIndex(int ItemIndex, int NewIndex);

	/*UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerCountMoney(int ItemIndex, int NewIndex);*/

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<UItemBase*> PlayerItems;

	bool ServerAddItem_Validate(UItemBase* Item);
	void ServerAddItem_Implementation(UItemBase* Item);

	bool ServerAddPickupItem_Validate(AItemPickupActor* Item);
	void ServerAddPickupItem_Implementation(AItemPickupActor* Item);

	bool ServerRemoveItem_Validate(UItemBase* Item);
	void ServerRemoveItem_Implementation(UItemBase* Item);

	void ServerRemoveItemByIndex_Implementation(int Index);

	void ServerChangeItemIndex_Implementation(int ItemIndex, int NewIndex);

private:	

	void AddItem(UItemBase* Item);

	UItemBase* FindItemByIndex(int Index);
	int FindIndexOfItem(UItemBase* Item);

	int FindIndexOfStackableItem(UItemBase* Item);
	bool CheckStackable(UItemBase* Item);
	int StackItem(int Index, UItemBase* Item);

};
