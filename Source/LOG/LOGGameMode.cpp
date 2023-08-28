// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOGGameMode.h"
#include "LOGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LOG/01_DataTable/LevelDataTable.h"

ALOGGameMode::ALOGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
