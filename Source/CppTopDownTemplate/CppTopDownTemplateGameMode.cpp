// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppTopDownTemplateGameMode.h"
#include "CppTopDownTemplatePlayerController.h"
#include "CppTopDownTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppTopDownTemplateGameMode::ACppTopDownTemplateGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACppTopDownTemplatePlayerController::StaticClass();
}