// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankTrackNew.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankAimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetTrackReferences();

	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &ATank::Fire);
	PlayerInputComponent->BindAxis(FName("TankTrack_Left"), LeftTrack, &UTankTrackNew::SetThrottle);
	PlayerInputComponent->BindAxis(FName("TankTrack_Right"), RightTrack, &UTankTrackNew::SetThrottle);
}

void ATank::AimAt(FVector WorldSpaceCoordinate) {
	TankAimComponent->AimAt(WorldSpaceCoordinate, ProjectileSpeed);
}

void ATank::SetTankBarrelComponent(UTankBarrel* BarrelComponent) {
	TankBarrel = BarrelComponent;
	TankAimComponent->SetBarrelComponent(BarrelComponent);
}

void ATank::SetTankTurretComponent(UTankTurret* TurretComponent) {
	TankAimComponent->SetTurretComponent(TurretComponent);
}

void ATank::Fire() {
	bool bHasReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds;
	if (TankBarrel && bHasReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, TankBarrel->GetSocketLocation("BarrelProjectileSpawn"), TankBarrel->GetSocketRotation("BarrelProjectileSpawn"));
		Projectile->Launch(ProjectileSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::SetTrackReferences() {
	for (auto& TrackComponent : GetComponentsByClass(UTankTrackNew::StaticClass())) {
		UTankTrackNew* Track = Cast<UTankTrackNew>(TrackComponent);
		if (TrackComponent->GetName() == FString("LeftTrackNew")) {
			this->LeftTrack = Track;
			UE_LOG(LogTemp, Warning, TEXT("LeftTrack assigned"))
		}
		if (TrackComponent->GetName() == FString("RightTrackNew")) {
			this->RightTrack = Track;
			UE_LOG(LogTemp, Warning, TEXT("RightTrack assigned"))
		}
	}
}
