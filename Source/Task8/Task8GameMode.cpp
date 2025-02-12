// Copyright Epic Games, Inc. All Rights Reserved.

#include "Task8GameMode.h"
#include "Task8Character.h"
#include "UObject/ConstructorHelpers.h"

ATask8GameMode::ATask8GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
