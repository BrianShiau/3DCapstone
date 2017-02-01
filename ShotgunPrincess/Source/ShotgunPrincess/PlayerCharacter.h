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

	// The Player's Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPlayerInventory* PlayerInventory;

	// The Player's Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Health;

	// Time player since the player last lost health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TimeSinceHealthLoss;

	// Time player last used dash
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float dashLastUsed;

	// Camera Sphere Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CameraSphere;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

  // Turn speed
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  float BaseTurnRate;

  // Lookup speed
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  float BaseLookUpRate;

	// Temporary Variable to offset Projectile
	UPROPERTY(EditAnywhere)
	float ProjectileOffset;

  // Projectile class to spawn
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TSubclassOf<class AProjectile> ProjectileClass;

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

	// Causes the Player to take damage
  void PlayerTakeDamage(int damage);

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Getter Methods
public:
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
