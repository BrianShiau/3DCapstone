// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SHOTGUNPRINCESS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
    
    // Camera boom for positioning
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;
    
    // The Camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;
    
public:
	// Sets default values for this character's properties
	APlayerCharacter();

    // Turn speed
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float BaseTurnRate;
    
    // Lookup speed
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float BaseLookUpRate;
    
    // Projectile class to spawn
    UPROPERTY(EditDefaultsOnly, Category=Projectile)
    TSubclassOf<class ATestProjectile> ProjectileClass;
    
    // Whether to use motion controller location for aiming (Once actual animations are created)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    uint32 bUsingMotionControllers : 1;
    
    // Called for pressing the fire button
    void OnFire();
    
    // Called for releasing the fire button
    void OnStopFire();

	// Called on the shift button being pressed
	void Dash();
    
    // Called for vertical input
    void MoveForward(float Value);
    
    // Called for horizontal input
    void MoveRight(float Value);
    
    // Input to turn at a normalized rate (for joystick)
    void TurnAtRate(float Rate);
    
    // Input to look up at a normalized rate (for joystick)
    void LookUpAtRate(float Rate);
    
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Getter Methods
public:
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
