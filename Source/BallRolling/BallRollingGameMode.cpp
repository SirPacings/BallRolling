// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallRollingGameMode.h"
#include "BallRollingBall.h"

ABallRollingGameMode::ABallRollingGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = ABallRollingBall::StaticClass();
}
