// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScuttleActor.generated.h"

UCLASS()
class SHOTGUNPRINCESS_API AScuttleActor : public AActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly)
    class USphereComponent* SightRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

public:

	// Set in BluePrints
	UPROPERTY(EditAnywhere)
	class ACharacter* PlayerCharacter;

    UPROPERTY(EditAnywhere)
    float TimeTillMove;

    UPROPERTY(EditAnywhere)
    float Accuracy;

    UPROPERTY(EditAnywhere)
    float FireRate;

    UPROPERTY(EditAnywhere)
    FVector WallNormal;

	UPROPERTY(EditAnywhere)
	float MaxMoveDistance;

    UPROPERTY(EditAnywhere)
    float RangeRadius;

    // Set in BluePrints
    UPROPERTY(EditAnywhere, Category=Projectile)
    TSubclassOf<class AProjectile> ProjectileClass;

    // modifiers
    float CurrentTimeToMove;
    float CurrentTimeToFire;
    bool bPlayerInRange;

    void OnFire();

    void OnStopFire();

    void Move();

    FVector Aim();

	// Sets default values for this actor's properties
	AScuttleActor();

	UFUNCTION(BlueprintCallable, Category="Initialize")
	void SetReferenceToPlayer(ACharacter* Ref);

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // Creates the sight range
    virtual void BeginPlay() override;

    // Getter Methods
    FORCEINLINE class USphereComponent* GetSightRange() const { return SightRange; }
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return Mesh; }
};
