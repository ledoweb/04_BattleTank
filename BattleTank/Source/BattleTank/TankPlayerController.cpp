// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimComponent.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetTank() const{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	if (GetTank()) {
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller possessing %s"), *GetTank()->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector AimPointDirection;
	if (GetAimPointWorldDirection(AimPointDirection)) {
		FVector AimHitLocation;
		if (GetAimHitLocation(AimHitLocation, AimPointDirection)) {
			//UE_LOG(LogTemp, Warning, TEXT("Aim hit location is at: %s"), *AimHitLocation.ToString());
			GetTank()->TankAimComponent->AimAt(AimHitLocation);
		}
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* Tank = Cast<ATank>(InPawn);
		if (Tank) {
			Tank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
		}
	}
}

bool ATankPlayerController::GetAimPointWorldDirection(FVector& direction) {
	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);

	FVector WorldPosition;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairPositionX * ViewportSize.X, CrosshairPositionY * ViewportSize.Y, WorldPosition, WorldDirection)) {
		direction = WorldDirection;
		return true;
	}
	return false;
}

bool ATankPlayerController::GetAimHitLocation(FVector &result, FVector direction) {
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, CameraLocation + (AimDistance * direction), ECollisionChannel::ECC_Camera)) {
		result = HitResult.Location;
		return true;
	}
	result = FVector(0.0);
	return false;
}

void ATankPlayerController::OnDeath() {
	UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *GetPawn()->GetName());
	StartSpectatingOnly();
}