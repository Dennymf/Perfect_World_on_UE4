// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perfect_WorldGameMode.h"
#include "../Character/Perfect_WorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

APerfect_WorldGameMode::APerfect_WorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
