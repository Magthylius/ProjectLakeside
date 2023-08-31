// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/PL_GameModeBase.h"
#include "Core/PL_MainCharacter.h"
#include "UObject/ConstructorHelpers.h"

APL_GameModeBase::APL_GameModeBase()
{
	DefaultPawnClass = APL_MainCharacter::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_Project/Blueprints/Core/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
