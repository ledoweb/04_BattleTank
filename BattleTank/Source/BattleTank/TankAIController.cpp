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
	auto ControlledTank = GetPawn();
	auto TankAimComponent = Cast<UTankAimComponent>(ControlledTank->GetComponentByClass(UTankAimComponent::StaticClass()));
	auto PlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetTank();

	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRangeToPlayer);

		if (ensure(ControlledTank) && ensure(TankAimComponent)) {
			TankAimComponent->AimAt(PlayerTank->GetActorLocation());

			if (TankAimComponent->AimState == EAimState::Locked) {
				TankAimComponent->Fire();
			}
		}
	}
}