// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "Door.h"
#include "PlayerCharacter.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	needsKey = false;
	isOpen = false;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	

	// Set up Collision
	TArray<UStaticMeshComponent*> Components;
	GetComponents(Components);

	//There's only one.
	StaticMeshComponent = Components[0];
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ADoor::OnHit);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("Component #%d"), i));
	
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	OpenDoor();
	CloseDoor();

}

void ADoor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter *player = Cast<APlayerCharacter>(OtherActor);
			if (player) {
				player->NearDoor(this);
				Interactor = player;
			}
		}
	}
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter *player = Cast<APlayerCharacter>(OtherActor);
			if (player) {
				
			}
		}
	}
}

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			APlayerCharacter *player = Cast<APlayerCharacter>(OtherActor);
			if (player) {
				
			}
		}
	}
}

void ADoor::OpenDoor() {

	if (Interactor != NULL) {
		if (Interactor->getIsOpeningDoor() && isOpen == false) {
			
			//GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 90.f));
			StaticMeshComponent->SetRelativeLocation(FVector(0.f, 80.f, 0.f));
			isOpen = true;
		}
	}
}

void ADoor::CloseDoor() {

}