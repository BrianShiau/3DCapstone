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
	
};
