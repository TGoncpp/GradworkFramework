// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gradwork_npcAIGameMode.h"
#include "Gradwork_npcAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AGradwork_npcAIGameMode::AGradwork_npcAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Hero"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
}

void AGradwork_npcAIGameMode::BeginPlay()
{
	//get refrence to game instance
	UGameInstance* gameInstance = GetWorld()->GetGameInstance();

	//Create instance off a player and his controller
	FString errorMessage;
	ULocalPlayer* player = gameInstance->CreateLocalPlayer(0, errorMessage, true);
	checkf(player, TEXT("local player failed load"));
}