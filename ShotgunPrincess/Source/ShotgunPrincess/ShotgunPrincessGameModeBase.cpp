// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "ShotgunPrincessGameModeBase.h"
#include "PlayerCharacter.h"

AShotgunPrincessGameModeBase::AShotgunPrincessGameModeBase() {
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BlueprintSource/Player/PlayerCharacterTest"));
    if (PlayerPawnBPClass.Class != NULL) {
        DefaultPawnClass = PlayerPawnBPClass.Class;
        UE_LOG(LogTemp, Log, TEXT("SUCCESS"));
    } else {
        UE_LOG(LogTemp, Log, TEXT("ERROR, Default Pawn Class Not Found"));
    }

	static ConstructorHelpers::FObjectFinder<UClass> HUDFinder(TEXT("/Game/BluePrintSource/HUD/MainHUD.MainHUD_C"));
	HUDClass = (UClass *)HUDFinder.Object;
}

