// Copyright Epic Games, Inc. All Rights Reserved.

#include "URGGameMode.h"
#include "URGPawn.h"
#include "URGHud.h"

AURGGameMode::AURGGameMode()
{
	DefaultPawnClass = AURGPawn::StaticClass();
	HUDClass = AURGHud::StaticClass();
}
