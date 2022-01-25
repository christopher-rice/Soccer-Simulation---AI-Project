// Copyright Epic Games, Inc. All Rights Reserved.


#include "FinalProjectGameModeBase.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFinalProjectGameModeBase::AFinalProjectGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PlayerCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

