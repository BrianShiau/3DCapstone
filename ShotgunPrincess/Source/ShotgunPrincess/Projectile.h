// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SHOTGUNPRINCESS_API AProjectile : public AActor
{
	GENERATED_BODY()

	// Sphere Collision Component
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* CollisionComponent;

	// Projectile Movement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SphereMesh;

public:
	// Hacky Solution to player projectile impulse bug
	UPROPERTY(EditAnywhere)
	class APlayerCharacter* PlayerReference;

	// if the projectile was fired by the player
	UPROPERTY(EditAnywhere)
	bool bFiredByPlayer;

	// Sets default values for this actor's properties
	AProjectile();

	// Called when there is a collision
	UFUNCTION()
	//void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Getter Methods
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComponent; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
