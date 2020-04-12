// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

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

	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Rounds == 0) {
		AimState = EAimState::OutOfAmmo;
		return;
	}

	if (FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds) {
		UE_LOG(LogTemp, Warning, TEXT("%s vs %s"), *AimDirection.ToString(), *BarrelComponent->GetForwardVector().ToString())
		if (BarrelComponent->GetForwardVector().Equals(AimDirection, 0.2)) {
			AimState = EAimState::Locked;
		}
		else {
			AimState = EAimState::Aiming;
		}
	}
}

void UTankAimComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret) {
	this->BarrelComponent = Barrel;
	this->TurretComponent = Turret;
}

void UTankAimComponent::AimAt(FVector WorldSpaceCoordinate) {
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
	this->AimDirection = AimDirection;
	auto BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	BarrelComponent->Elevate(DeltaRotator.Pitch);
}

void UTankAimComponent::Fire() {
	bool bHasReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds;
	if (BarrelComponent && (AimState == EAimState::Reloading || AimState == EAimState::Locked)) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, BarrelComponent->GetSocketLocation("BarrelProjectileSpawn"), BarrelComponent->GetSocketRotation("BarrelProjectileSpawn"));
		Projectile->Launch(ProjectileSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AimState = EAimState::Reloading;
		Rounds--;
	}
}


