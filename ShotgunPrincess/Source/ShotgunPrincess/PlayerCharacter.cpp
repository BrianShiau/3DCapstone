// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "PlayerInventory.h"
#include "Door.h"

namespace {
	const FVector kBaseDashVector = FVector(0, 4000, 0);
	const FVector kUpgradedDashVector = FVector(0, 8000, 0);
	const float dashCooldown = 2.0f;
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);


    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
    ProjectileOffset = 100.f;

	dashLastUsed = 0.f;

    // Player controllers are used to control Pawns if specified to true
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = true;

    // Sets the players movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Creates the Camera Boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 100.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 0.f);
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.0f, 55.f));
    //CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bUseControllerViewRotation = true;

    // Create the Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

	//Create camera sphere collider
	CameraSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CameraSphere"));
	CameraSphere->SetSphereRadius(12.f);
	CameraSphere->SetupAttachment(Camera);

	// Create the Player's Inventory
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("Inventory"));

	// Set the Player's default health
	Health = 100;

	isNearDoor = false;
	isOpeningDoor = false;
	aDoor = NULL;
	MaxHealth = 100;
	Health = MaxHealth;
	TimeSinceHealthLoss = 100;

	// Set Time between attacks
	FireCooldown = .3;
	LastFired = -FireCooldown - 1;
	Firing = false;
}

void APlayerCharacter::MoveForward(float Value) {
    if (Controller != NULL && Value != 0.f) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Forward, Value);
        //UE_LOG(LogTemp, Log, TEXT("MOVING FORWARD"));
    }
}

void APlayerCharacter::MoveRight(float Value) {
    if (Controller != NULL && Value != 0.f) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Forward, Value);
        //UE_LOG(LogTemp, Log, TEXT("MOVING RIGHT"));
    }
}

void APlayerCharacter::TurnAtRate(float Rate) {
    if (Rate != 0.f) {
        //UE_LOG(LogTemp, Log, TEXT("TURNING"));
        AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
    }
}

void APlayerCharacter::LookUpAtRate(float Rate) {
    if (Rate != 0.f) {
        //UE_LOG(LogTemp, Log, TEXT("LOOKING UP"));
        AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
    }
}

void APlayerCharacter::InvertMouseLookUp(float Rate) {
    if (Rate != 0.f) {
		AddControllerPitchInput(-1 * Rate);
    }
}

void APlayerCharacter::OnFire() {
	if (LastFired + FireCooldown < GetWorld()->GetTimeSeconds()) {
		Firing = true;
	}
}

void APlayerCharacter::OnStopFire() {
	Firing = false;
}

void APlayerCharacter::Dash() {

	const APlayerController* playerController = Cast<APlayerController>(GetController());
	// Get Player movement component
	UCharacterMovementComponent* const movementComponent = GetCharacterMovement();
	const float currentTime = GetWorld()->GetTimeSeconds();
	if (nullptr != InputComponent && nullptr != playerController && currentTime >= dashLastUsed + dashCooldown && movementComponent->IsMovingOnGround()) {
		// Grab Y velocity and clamp it to -1.0f < x < 1.0f;
		const float dashDirection = FMath::Clamp(GetVelocity().Y, -1.0f, 1.0f);
		// Check if player has dash upgrade
		const bool hasDashUpgrade = PlayerInventory->HasDashBoots;
		// If has dash upgrade, use upgraded dash vector, else use base dash vector
		const FVector dashVector = hasDashUpgrade ? kUpgradedDashVector : kBaseDashVector;
		// Launch the player in the direction they're moving at a force chosen based off of their upgrade status
		movementComponent->Launch(dashDirection * dashVector);
		// Set the dash last used time
		dashLastUsed = currentTime;
	}

}

void APlayerCharacter::Interact() {

	if (isNearDoor) {
		// Open the Door
		isOpeningDoor = true;
		isNearDoor = false;
	}
}

void APlayerCharacter::NearDoor(ADoor* someDoor) {
	//TODO: Change text
	bool branchText = someDoor->Openable();
	if(branchText) GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, "Press 'F' to Open the Door");
	else GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, "Find the Key for this Door");
	isNearDoor = true;
	if (someDoor != NULL) {

		aDoor = someDoor;
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

    // turn is for mouse
    // turn rate is for joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::InvertMouseLookUp);
    PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);


}

// Causes the Player to take damage
void APlayerCharacter::PlayerTakeDamage(int damage) {
	//UE_LOG(LogTemp, Warning, TEXT("Health: %d"), Health);
	Health -= damage;
	TimeSinceHealthLoss = 0;
	if (Health <= 0) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCapsuleComponent()->IsOverlappingComponent(CameraSphere)) {
		GetMesh()->SetOwnerNoSee(true);
	}
	else {
		GetMesh()->SetOwnerNoSee(false);
	}

	TimeSinceHealthLoss += GetWorld()->GetDeltaSeconds();

	if (TimeSinceHealthLoss > 3 && Health < MaxHealth) {
		Health++;
	}

	//if (Firing) {
	//	if (LastFired + FireCooldown < GetWorld()->GetTimeSeconds()) {
	//		//UE_LOG(LogTemp, Log, TEXT("FIRING"));
	//		if (ProjectileClass != NULL)
	//		{
	//			UWorld* const World = GetWorld();
	//			if (World != NULL) {
	//				const FRotator SpawnRotation = GetControlRotation();
	//				const FVector SpawnLocation = GetActorLocation();
	//				AProjectile* bullet = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation + SpawnRotation.Vector() * ProjectileOffset, SpawnRotation);
	//				bullet->PlayerReference = this;
	//				bullet->bFiredByPlayer = true;
	//			}
	//			LastFired = GetWorld()->GetTimeSeconds();
	//		}
	//		else {
	//			UE_LOG(LogTemp, Log, TEXT("ERROR :: PROJECTILE CLASS IS NOT SET"));
	//		}
	//	}
	//}
}
