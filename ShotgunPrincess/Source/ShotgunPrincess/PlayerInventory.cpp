// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "PlayerInventory.h"


// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	ResetInventory();
}

void UPlayerInventory::ResetInventory()
{
	HasDashBoots = false;
	keys.Empty();
}

void UPlayerInventory::AddKey(FName keyName)
{
	keys.Add(keyName);
}

bool UPlayerInventory::HasKey(FName keyName) const {
	return keys.Contains(keyName);
}