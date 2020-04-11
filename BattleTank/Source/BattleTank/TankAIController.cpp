// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetTank();

	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRangeToPlayer);

		if (ensure(ControlledTank)) {
			ControlledTank->TankAimComponent->AimAt(PlayerTank->GetActorLocation());
			ControlledTank->TankAimComponent->Fire();
		}
	}
}