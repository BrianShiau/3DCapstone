// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "Projectile.h"
#include "PlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set up Collision Component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(5.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComponent->OnActorHit.AddDynamic(this, &AProjectile::OnHit);

	// Players can not walt on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);

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
		//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Materials/FresnelBR.FresnelBR"));
		//UMaterial* TheMaterial = (UMaterial*)Material.Object;
		//UMaterialInstanceDynamic* TheMaterial_Dyn = UMaterialInstanceDynamic::Create(TheMaterial, SphereMesh);
		//SphereMesh->SetMaterial(0, TheMaterial_Dyn));

		SphereMesh->SetStaticMesh(SphereVisualAsset.Object);
		SphereMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereMesh->SetWorldScale3D(FVector(0.8f));
	}

	bFiredByPlayer = false;

	// Die After 3 Secs
	InitialLifeSpan = 6.f;

	this->OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Log, TEXT("WHATA"));
	if ((OtherActor != NULL) && (OtherActor != this) && (SelfActor != NULL)) {
		if (!bFiredByPlayer && OtherActor == PlayerReference) {
			PlayerReference->PlayerTakeDamage(18);
			//Destroy();
			//UE_LOG(LogTemp, Log, TEXT("Player Hit"));
		} else {
			//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.f, GetActorLocation());
			//Destroy();
			//UE_LOG(LogTemp, Log, TEXT("Non Player Hit"));
		}
	}
}
