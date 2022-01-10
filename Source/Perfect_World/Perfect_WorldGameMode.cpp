// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perfect_WorldGameMode.h"
#include "Perfect_WorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

APerfect_WorldGameMode::APerfect_WorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
