// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "PlayerInventory.h"

namespace {
	const FVector kBaseDashVector = FVector(0, 4000, 0);
	const FVector kUpgradedDashVector = FVector(0, 4000, 0);
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
    ProjectileOffset = 100.f;

    // Player controllers are used to control Pawns if specified to true
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Sets the players movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Creates the Camera Boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 100.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 0.f); //Setting the Relative Location Z value didnt work so I put that value in the socket offset. The Y value is correct.
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.0f, 55.f));
    CameraBoom->bUsePawnControlRotation = true; // rotate the arm based on the controller

    // Create the Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

	// Create the Player's Inventory
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("Inventory"));

    bUsingMotionControllers = false;

	// Set the Player's default health
	Health = 100;
}

void APlayerCharacter::MoveForward(float Value) {
    if (Controller != NULL && Value != 0.f) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Forward, Value);
        UE_LOG(LogTemp, Log, TEXT("MOVING FORWARD"));
    }
}

void APlayerCharacter::MoveRight(float Value) {
    if (Controller != NULL && Value != 0.f) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Forward, Value);
        UE_LOG(LogTemp, Log, TEXT("MOVING RIGHT"));
    }
}

void APlayerCharacter::TurnAtRate(float Rate) {
    if (Rate != 0.f) {
        UE_LOG(LogTemp, Log, TEXT("TURNING"));
        AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
    }
}

void APlayerCharacter::LookUpAtRate(float Rate) {
    if (Rate != 0.f) {
        UE_LOG(LogTemp, Log, TEXT("LOOKING UP"));
        AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
    }
}

void APlayerCharacter::OnFire() {
    UE_LOG(LogTemp, Log, TEXT("FIRING"));
    if (ProjectileClass != NULL)
    {
        UWorld* const World = GetWorld();
        if (World != NULL) {
            if (bUsingMotionControllers)
            {
                //const FRotator SpawnRotation = GetActorRotation();
                const FRotator SpawnRotation = GetControlRotation();
                const FVector SpawnLocation = GetActorLocation();
                World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
            } else {
                //const FRotator SpawnRotation = GetActorRotation();
                const FRotator SpawnRotation = GetControlRotation();
                const FVector SpawnLocation = GetActorLocation();
                AProjectile* bullet = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation + SpawnRotation.Vector() * ProjectileOffset, SpawnRotation);
                bullet->PlayerReference = this;
            }
        }
    }
}

void APlayerCharacter::OnStopFire() {
    // does nothing for now
}

void APlayerCharacter::Dash() {

	const APlayerController* playerController = Cast<APlayerController>(GetController());
	if (nullptr != InputComponent && nullptr != playerController) {
		// Grab axis of movement on Y, value either -1.0f or 1.0f on keyboard. When controller added, need to update.
		const float dashDirection = InputComponent->GetAxisValue(TEXT("MoveRight"));
		// Get Player movement component
		UCharacterMovementComponent* const movementComponent = playerController->GetCharacter()->GetCharacterMovement();
		// Launch the player in the direction they're moving at a force chosen based off of their upgrade status
		movementComponent->Launch(dashDirection * kBaseDashVector);
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("FirePrimary", IE_Pressed, this, &APlayerCharacter::OnFire);
    PlayerInputComponent->BindAction("FirePrimary", IE_Released, this, &APlayerCharacter::OnStopFire);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);

    // turn is for mouse
    // turn rate is for joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);


}

// Causes the Player to take damage
void APlayerCharacter::PlayerTakeDamage(int damage) {
	UE_LOG(LogTemp, Warning, TEXT("Health: %d"), Health);
	Health -= damage;
	if (Health <= 0) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}
