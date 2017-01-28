// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set up Collision Component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(5.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// Players can not walt on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	// Set Collision Component as Root Component
	if (!SetRootComponent(CollisionComponent)) { UE_LOG(LogTemp, Log, TEXT("ERROR, Could Not Set Root Component")); }

	// Set up the Projectile Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 0;

	// Set up the Sphere Visuals
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereVisuals"));
	SphereMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereVisualAsset.Object);
		SphereMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereMesh->SetWorldScale3D(FVector(0.8f));
	}

	// Die After 3 Secs
	InitialLifeSpan = 3.f;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()) {
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.f, GetActorLocation());
		Destroy();
	}
}

