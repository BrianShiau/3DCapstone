// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "ScuttleActor.h"
//#include "Projectile.h"

// Sets default values
AScuttleActor::AScuttleActor()
{
    // Specify that there will be a tick method
	/*PrimaryActorTick.bCanEverTick = true;
    
    // Get the Player Character from the world
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    TimeTillMove = 3.f;
    Accuracy = 0.f;
    FireRate = 5.f;
    WallNormal = FVector(0.f, 0.f, 1.f);
    RangeRadius = -1.f;
    
    CurrentTimeToMove = TimeTillMove;
    CurrentTimeToFire = FireRate;
    bPlayerInRange = true;*/
}

// Called every frame
void AScuttleActor::Tick( float DeltaTime )
{
	//Super::Tick( DeltaTime );
    
    //CurrentTimeToMove -= DeltaTime;
    
    //if (bPlayerInRange) CurrentTimeToFire -= DeltaTime;
    
    //if (CurrentTimeToMove < 0.f) Move();
    
    //if (CurrentTimeToFire < 0.f) OnFire();
}

// Creates the sight range
void AScuttleActor::BeginPlay() {
    // to be implemented
}

// logic for spawning a projectile actor and setting its inital conditions
/*void AScuttleActor::OnFire() {
    // to be implemented
    
    CurrentTimeToFire = FireRate;
}

// here just in case there is a charge mechanic, ending animation, etc.
void AScuttleActor::OnStopFire() {
    // maybe implement
}

void AScuttleActor::Move() {
    // to be implemented
    
    CurrentTimeToMove = TimeTillMove;
}*/

//FVector AScuttleActor::Aim() {
//    // to be implemented
//
//    return FVector(0.f, 1.f, 0.f);
//}
