// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "EndLevelTrigger.h"


// Sets default values
AEndLevelTrigger::AEndLevelTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up Collision
	TArray<UStaticMeshComponent*> Components;
	GetComponents(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		UStaticMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &AEndLevelTrigger::OnHit);
	}
}

// Called every frame
void AEndLevelTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEndLevelTrigger::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//Test for player eventually?
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}