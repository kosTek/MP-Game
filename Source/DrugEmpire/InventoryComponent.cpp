// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemBase.h"
#include "ItemPickupActor.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxInventoryItems = 5;

}


// Called when the game starts
void UInventoryComponent::BeginPlay(){
	Super::BeginPlay();

	// ...
	
}

bool UInventoryComponent::ServerAddItem_Validate(UItemBase* Item) {
	if (Item == nullptr) { return false; }

	if (PlayerItems.Num() + 1 >= MaxInventoryItems) {
		return false;
	}

	return true;
}

void UInventoryComponent::ServerAddItem_Implementation(UItemBase* Item) {

	PlayerItems.Add(Item);

	OnInventoryUpdate.Broadcast();
}

bool UInventoryComponent::ServerAddPickupItem_Validate(AItemPickupActor* Item) {
	if (Item == nullptr) { return false; }

	if (Item->ItemData == nullptr) { return false; }

	if (CheckStackable(Item->ItemData)) {
		return true;
	}

	if (PlayerItems.Num() + 1 >= MaxInventoryItems) {
		return false;
	}

	return true;
}

void UInventoryComponent::ServerAddPickupItem_Implementation(AItemPickupActor* Item) {

	if (CheckStackable(Item->ItemData)) {
		
		int ItemStackSize = Item->ItemData->StackSize;

		while (ItemStackSize > 0) { // While the stack is overflowing the maximum stack size

			UE_LOG(LogTemp, Warning, TEXT("[Stack Loop] %i - Stack Size to stack"), ItemStackSize);

			int StackableItemIndex = FindIndexOfStackableItem(Item->ItemData);

			if (StackableItemIndex == -1) {
				UE_LOG(LogTemp, Warning, TEXT("[Stack Loop] %i - Index"), StackableItemIndex);

				AddItem(Item->ItemData);

				break;
			} else {
				UE_LOG(LogTemp, Warning, TEXT("[Stack Loop] %i - Index"), StackableItemIndex);
				ItemStackSize -= StackItem(StackableItemIndex, Item->ItemData);
				Item->ItemData->StackSize = ItemStackSize;
			}

		}

	} else {
		AddItem(Item->ItemData);
	}

	Item->Destroy();

	OnInventoryUpdate.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Added new item! %i items in inventory"), PlayerItems.Num());
}

void UInventoryComponent::AddPickupItem(AItemPickupActor* Item) {

	ServerAddPickupItem(Item);

}

bool UInventoryComponent::ServerRemoveItem_Validate(UItemBase* Item) {

	if (PlayerItems.Contains(Item)) {
		return true;
	}

	return false;

}

void UInventoryComponent::ServerRemoveItem_Implementation(UItemBase* Item) {

	if (PlayerItems.Contains(Item)) {
		PlayerItems.Remove(Item);
		OnInventoryUpdate.Broadcast();
	}

}

void UInventoryComponent::ServerRemoveItemByIndex_Implementation(int Index) {

	for (int i = 0; i < PlayerItems.Num(); i++) {
		if (Index == PlayerItems[i]->Index) {
			PlayerItems.Remove(PlayerItems[i]);
			OnInventoryUpdate.Broadcast();
			break;
		}
	}

}

void UInventoryComponent::ServerChangeItemIndex_Implementation(int ItemIndex, int NewIndex) {

	UItemBase* FoundItem = FindItemByIndex(ItemIndex); // Check if the old index item exists
	UItemBase* FoundOverlapItem = FindItemByIndex(NewIndex); // Check if the new index has an item in it

	if (FoundItem) {

		if (FoundOverlapItem) {
			FoundOverlapItem->Index = ItemIndex;
		}

		FoundItem->Index = NewIndex;

		OnInventoryUpdate.Broadcast();

	}

}

void UInventoryComponent::AddItem(UItemBase* Item) {

	Item->Index = PlayerItems.Num();
	PlayerItems.Add(Item);

}

UItemBase* UInventoryComponent::FindItemByIndex(int Index) {

	for (int i = 0; i < PlayerItems.Num(); i++) {
		if (Index == PlayerItems[i]->Index) {
			return PlayerItems[i];
		}
	}

	return nullptr;
}

int UInventoryComponent::FindIndexOfItem(UItemBase* Item) {

	for (int i = 0; i < PlayerItems.Num(); i++) {
		if (PlayerItems[i] == Item) {
			return i;
		}
	}

	return -1;
}



int UInventoryComponent::FindIndexOfStackableItem(UItemBase* Item) {

	for (int i = 0; i < PlayerItems.Num(); i++) {
		if (PlayerItems[i]->ItemType == Item->ItemType) {
			
			if (PlayerItems[i]->StackSize >= PlayerItems[i]->MaxStackSize) {
				continue;
			} else {
				return i;
			}

		}
	}

	return -1;
}

bool UInventoryComponent::CheckStackable(UItemBase* Item) {

	if (Item->ItemFlags.Contains(EItemFlag::STACKABLE)) {
		return true;
	}

	return false;
}

int UInventoryComponent::StackItem(int Index, UItemBase* Item) {

	if (Index == -1) { return -1; }

	if (PlayerItems[Index]->StackSize + Item->StackSize >= PlayerItems[Index]->MaxStackSize) {

		int CurrentStackSize = PlayerItems[Index]->StackSize;

		PlayerItems[Index]->StackSize = PlayerItems[Index]->MaxStackSize;
		
		UE_LOG(LogTemp, Warning, TEXT("[Stack Logic] %i - Remaining stack"), Item->StackSize - CurrentStackSize);

		return PlayerItems[Index]->MaxStackSize - Item->StackSize;

	}

	PlayerItems[Index]->StackSize += Item->StackSize;

	return PlayerItems[Index]->StackSize;

}