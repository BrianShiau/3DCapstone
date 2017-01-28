// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOTGUNPRINCESS_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

	// If the Player has the Dash Boots
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasDashBoots;

	// If the Player has the Ballroom Key
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasBallRoomKey;

	void ResetInventory();
};
