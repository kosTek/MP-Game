// Copyright Epic Games, Inc. All Rights Reserved.

#include "DrugEmpireGameMode.h"
#include "DrugEmpireCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADrugEmpireGameMode::ADrugEmpireGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
