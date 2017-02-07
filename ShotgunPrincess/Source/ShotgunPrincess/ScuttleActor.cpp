// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "ScuttleActor.h"
#include "PlayerCharacter.h"
#include "Projectile.h"

// Sets default values
AScuttleActor::AScuttleActor()
{
    // Specify that there will be a tick method
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

    TimeTillMove = 5.f;
    Accuracy = 0.f;
    FireRate = 1.0f;
    WallNormal = FVector(0.f, 0.f, 1.f);
    RangeRadius = -1.f;
	MaxMoveDistance = 200.f;

    CurrentTimeToMove = TimeTillMove;
    CurrentTimeToFire = FireRate;
    bPlayerInRange = true;

	// Set up the Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("/Game/Models/ScuttleOBJTest.ScuttleOBJTest"));
	if (VisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(VisualAsset.Object);
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
		Mesh->SetWorldScale3D(FVector(20.f));
	}
	SetActorScale3D(FVector(20.f, 20.f, 20.f));
	SetActorRotation(FRotator(90.f, 90.f, 90.f));
}

// Called every frame
void AScuttleActor::Tick( float DeltaTime )
{
	//UE_LOG(LogTemp, Log, TEXT("Current Time Till Move Is: %f"), CurrentTimeToMove);
	Super::Tick( DeltaTime );

    CurrentTimeToMove -= DeltaTime;
	//UE_LOG(LogTemp, Log, TEXT("Current Time Till Move Is: %f"), CurrentTimeToMove);

    if (bPlayerInRange) CurrentTimeToFire -= DeltaTime;

    if (CurrentTimeToMove < 0.f) Move();

    if (CurrentTimeToFire < 0.f) OnFire();
}

void AScuttleActor::SetReferenceToPlayer(APlayerCharacter* Ref) {
	PlayerCharacter = Ref;
	if (PlayerCharacter != NULL) {
		UE_LOG(LogTemp, Log, TEXT("SetPlayerCharacter"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("EveryThingISBROKEN"));
	}
}

// Creates the sight range
void AScuttleActor::BeginPlay() {
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), Actors);
	SetReferenceToPlayer((APlayerCharacter*)Actors[0]); // maybe put this in level blueprint later
}

// logic for spawning a projectile actor and setting its inital conditions
void AScuttleActor::OnFire() {
		//UE_LOG(LogTemp, Log, TEXT("Scuttle FIRING"));
		if (ProjectileClass != NULL)
		{
				UWorld* const World = GetWorld();
				if (World != NULL) {
						float ProjectileOffset = 100.0f;
						const FRotator SpawnRotation = GetActorRotation();
						const FRotator ScuttleRotator = FRotator(SpawnRotation.Pitch, SpawnRotation.Roll - 90.f, SpawnRotation.Yaw + 0.f);
						const FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
						//AProjectile* bullet = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation + ScuttleRotator.Vector() * ProjectileOffset, ScuttleRotator);
						//bullet->PlayerReference = PlayerCharacter;
						//bullet->bFiredByPlayer = false;
				}
		} else {
			UE_LOG(LogTemp, Log, TEXT("ERROR :: PROJECTILE CLASS IS NOT SET"));
		}

    CurrentTimeToFire = FireRate;
}

// here just in case there is a charge mechanic, ending animation, etc.
void AScuttleActor::OnStopFire() {
    // maybe implement
}

void AScuttleActor::Move() {
	//UE_LOG(LogTemp, Log, TEXT("EnemyMoving"));
	FVector MovementPlane = FVector(1.f, 1.f, 1.f);

	// Reduce the directions the enemy can move to only the plane it is standing one
	if (WallNormal[0] >= 0.f && WallNormal[1] >= 0.f && WallNormal[2] >= 0.f) {
		MovementPlane -= WallNormal;
	}
	else {
		MovementPlane += WallNormal;
	}

	// get the distance to move in both directions along the plane
	float AxisOne = FMath::RandRange(0.f, MaxMoveDistance);
	float AxisTwo = MaxMoveDistance - AxisOne;

	if (FMath::RandBool()) AxisOne *= -1.f;
	if (FMath::RandBool()) AxisTwo *= -1.f;

	if (MovementPlane[0] == 0.f) MovementPlane[1] = AxisOne;
	else MovementPlane[0] = AxisOne;

	if (MovementPlane[2] == 0.f) MovementPlane[1] = AxisTwo;
	else MovementPlane[2] = AxisTwo;

	// TODO :: use interpolation to make movement smooth

	SetActorLocation(GetActorLocation() + MovementPlane);

    CurrentTimeToMove = TimeTillMove;
}

FVector AScuttleActor::Aim() {
    // to be implemented

    return FVector(0.f, 1.f, 0.f);
}
