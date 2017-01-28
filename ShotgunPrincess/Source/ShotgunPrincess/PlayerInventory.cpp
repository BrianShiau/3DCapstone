// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "PlayerInventory.h"


// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	HasDashBoots = false;
	HasBallRoomKey = false;
}

void UPlayerInventory::ResetInventory()
{
	HasDashBoots = false;
	HasBallRoomKey = false;
}
