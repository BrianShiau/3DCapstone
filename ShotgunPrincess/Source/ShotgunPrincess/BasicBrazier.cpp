// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "BasicBrazier.h"
#include "PlayerCharacter.h"


// Sets default values
ABasicBrazier::ABasicBrazier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicBrazier::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up Collision
	TArray<UStaticMeshComponent*> Components;
	GetComponents(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		UStaticMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABasicBrazier::OnHit);
	}
}

// Called every frame
void ABasicBrazier::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABasicBrazier::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherActor->IsA(APlayerCharacter::StaticClass())) {
			//UE_LOG(LogTemp, Log, TEXT("FIIIRE"));
			APlayerCharacter *player = Cast<APlayerCharacter>(OtherActor);
			if (player) {
				player->TakeDamage(1);
			}
			//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
	}
}