// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "Door.h"
#include "PlayerCharacter.h"
#include "PlayerInventory.h"
#include <string>


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
			if (Openable()) {
				StaticMeshComponent->SetRelativeLocation(FVector(0.f, 80.f, 0.f));
				isOpen = true;
				Interactor->setIsOpeningDoor(false);
			}
		}
	}
}

bool ADoor::Openable() {
	bool keyFound = false;
	if (Interactor != NULL) {
		/*Conversion of Door Name to Key Name. Door1 -> Key1*/
		//FName to FString to std::string
		std::string cDoorName(TCHAR_TO_UTF8(*doorName.ToString()));
		std::string number = &cDoorName.back();
		std::string cKeyName = "Key" + number;
		//std::string to FString to FName
		FName keyName = FName(*FString(cKeyName.c_str()));
		UPlayerInventory* inventory = Interactor->getInventory();
		keyFound = inventory->HasKey(keyName);
	}
	return needsKey == false || keyFound;
}