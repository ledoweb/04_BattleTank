// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankTurret::UTankTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankTurret::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankTurret::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankTurret::RotateTowards(FVector Direction)
{
	auto CurrentRotation = GetForwardVector().Rotation();
	auto TargetRotation = Direction.Rotation();
	auto YawRotation = (TargetRotation - CurrentRotation).Yaw;
	if (FMath::Abs(YawRotation) > 180) {
		YawRotation = -YawRotation;
	}
	auto ClampedDelta = FMath::Clamp<float>(YawRotation, -1, 1);
	auto Delta = Speed * ClampedDelta * GetWorld()->DeltaTimeSeconds;
	AddLocalRotation(FRotator(0, Delta, 0));
}

