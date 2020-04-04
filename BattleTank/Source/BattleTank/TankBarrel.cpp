// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float Degrees) {
	Degrees = FMath::Clamp<float>(Degrees, -1, 1);
	auto ElevationChange = VerticalSpeed * Degrees * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinimumAngle, MaxiumAngle);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}