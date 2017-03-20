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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UPlayerInventory* PlayerInventory;

	// The Player's Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health;

	// The Player's Max Health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

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

	// Time shield last fired
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ShieldLastFired;

	// Time until shield can be fired again
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ShieldFireCooldown;

	// Whether the player is currently firing the shield (has pushed the shield button)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ShieldFiring;

	// Time player last used dash
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float dashLastUsed;

	// Camera Sphere Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CameraSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isOpeningDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
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

	// 1 = Shotgun, 2 = Pistol, 3 = TBD, 4 = ???, 5 = Shield
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> WeaponsAcquired;

	// Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WeaponType;

	// Previous projectile class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PreviousWeaponType;

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

	//Called when player is near a door
	void AwayDoor(ADoor* someDoor);

  // Called for vertical input
  void MoveForward(float Value);

  // Called for horizontal input
  void MoveRight(float Value);

  // Input to turn at a normalized rate (for joystick)
  void TurnAtRate(float Rate);

  // Input to look up at a normalized rate (for joystick)
  void LookUpAtRate(float Rate);

  // Input to invert look up controls
  void InvertMouseLookUp(float Rate);

  // Called when the player wants to switch to the seventh weapon
  void Weapon7();

  // Called when the player wants to switch to the sixth weapon
  void Weapon6();

  // Called when the player wants to switch to the fifth weapon
  void Weapon5();

  // Called when the player wants to switch to the fourth weapon
  void Weapon4();

  // Called when the player wants to switch to the third weapon
  void Weapon3();

  // Called when the player wants to switch to the second weapon
  void Weapon2();

  // Called when the player wants to switch to the first weapon
  void Weapon1();

  // Helper method for weapon swapping
  void SwapToWeapon(int weaponType);

  // Called when the player wants to use the shield
  void Shield();

  // Called when the player wants to swap weapons
  void SwapWeapons();

	// Causes the Player to take damage
  UFUNCTION(BlueprintCallable, Category="Attack")
  void PlayerTakeDamage(float damage);

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
	FORCEINLINE class UPlayerInventory* getInventory() const { return PlayerInventory; }
};
