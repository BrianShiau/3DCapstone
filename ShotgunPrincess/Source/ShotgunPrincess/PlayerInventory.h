// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOTGUNPRINCESS_API UPlayerInventory : public UActorComponent
{
private:
	GENERATED_BODY()
	class TArray<FName> keys;

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

	void ResetInventory();

	// If the Player has the Dash Boots
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasDashBoots;

	UFUNCTION(BlueprintCallable, Category="C++")
	void AddKey(FName keyName);

	UFUNCTION(BlueprintCallable, Category="C++")
	bool HasKey(FName keyName) const;

	UFUNCTION(BlueprintCallable, Category = "C++")
	bool KeyRequirementMet(int NeededKeys) const;

	UFUNCTION(BlueprintCallable, Category = "C++")
	int NumKeys() const;

	
};
