// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/PL_GameModeBase.h"
#include "Core/PL_MainCharacter.h"
#include "UObject/ConstructorHelpers.h"

APL_GameModeBase::APL_GameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
