// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

void UItemBase::OnUse() {

	UE_LOG(LogTemp, Warning, TEXT("[Item] %s - Use called! Default not overwritten!"));

}

void UItemBase::OnDrop() {

	UE_LOG(LogTemp, Warning, TEXT("[Item] %s - Drop called! Default not overwritten!"));

}

void UItemBase::OnEquip() {

	UE_LOG(LogTemp, Warning, TEXT("[Item] %s - Equip called! Default not overwritten!"));

}
