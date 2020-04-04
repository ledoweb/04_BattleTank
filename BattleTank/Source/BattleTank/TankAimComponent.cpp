// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimComponent::AimAt(FVector WorldSpaceCoordinate, float ProjectileSpeed) {
	FVector ProjectileStartPosition = BarrelComponent->GetSocketLocation(FName("BarrelProjectileSpawn"));
	FVector OutProjectileVector;
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutProjectileVector, ProjectileStartPosition, WorldSpaceCoordinate, ProjectileSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto NormalizedProjectileDirection = OutProjectileVector.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming with projectile direction: %s"), *GetOwner()->GetName(), *NormalizedProjectileDirection.ToString())
		MoveBarrelTowards(NormalizedProjectileDirection);
		TurretComponent->RotateTowards(NormalizedProjectileDirection);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("No aiming solution found!"))
	}
}

void UTankAimComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	BarrelComponent->Elevate(DeltaRotator.Pitch);
}

void UTankAimComponent::SetBarrelComponent(UTankBarrel* BarrelComponent) {
	this->BarrelComponent = BarrelComponent;
}

void UTankAimComponent::SetTurretComponent(UTankTurret* TurretComponent) {
	this->TurretComponent = TurretComponent;
}

