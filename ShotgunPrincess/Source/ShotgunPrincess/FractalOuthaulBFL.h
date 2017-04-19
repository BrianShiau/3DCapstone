// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FractalOuthaulBFL.generated.h"

/**
 *
 */
UCLASS()
class SHOTGUNPRINCESS_API UFractalOuthaulBFL : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()

    // returns the rotation necessary to hit a moving target
	UFUNCTION(BlueprintCallable, Category="AI")
    static FRotator RotationToHit(AActor* firer, AActor* target, float bulletVelocity);

    // returns the rotation necessary to hit a moving target
    UFUNCTION(BlueprintCallable, Category="AI")
    static FRotator RotationToHitFromVector(FVector fireLocation, FVector targetLocation, FVector targetVelocity, float bulletVelocity);

	// returns if the input float is between the given values
	UFUNCTION(BlueprintCallable, Category="Utility")
	static bool IsBetween(float input, float min, float max);

	// returns if the input int is between the given values
	UFUNCTION(BlueprintCallable, Category="Utility")
	static bool IsBetweenInt(int input, int min, int max);

	// returns a random value not including the specified
	UFUNCTION(BlueprintCallable, Category="Utility")
	static int RandomIntegerExclude(int max, int exclude);
};
