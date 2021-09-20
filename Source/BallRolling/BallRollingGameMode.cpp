// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallRollingGameMode.h"
#include "ControllerPawn.h"

ABallRollingGameMode::ABallRollingGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = AControllerPawn::StaticClass();
}
