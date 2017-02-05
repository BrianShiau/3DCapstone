// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SHOTGUNPRINCESS_API APlayerCharacter : public ACharacter
{
  GENERATED_BODY()

  // Camera boom for positioning
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
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

	// The Player's Max Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxHealth;

	// Time player since the player last lost health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TimeSinceHealthLoss;

	// Time player last fired
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LastFired;

	// Time until player can fire again
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireCooldown;

	// Whether the player is currently firing (holding down the mouse button)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Firing;

	// Time player last used dash
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float dashLastUsed;

	// Camera Sphere Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CameraSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isOpeningDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isNearDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ADoor* aDoor;

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

  // Called for pressing the fire button
  void OnFire();

  // Called for releasing the fire button
  void OnStopFire();

	// Called on the shift button being pressed
	void Dash();

  // Called for pressing interaction button
	void Interact();

	//Called when player is near a door
	void NearDoor(ADoor* someDoor);

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

// Getter and Setter Methods
public:
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE bool getIsOpeningDoor() { return isOpeningDoor;  }
	FORCEINLINE void setIsOpeningDoor(bool bDoor) { isOpeningDoor = bDoor; }
};
