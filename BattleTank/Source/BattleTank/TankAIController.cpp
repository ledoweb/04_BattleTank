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

	if (PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRangeToPlayer);

		if (ControlledTank && TankAimComponent) {
			TankAimComponent->AimAt(PlayerTank->GetActorLocation());

			if (TankAimComponent->AimState == EAimState::Locked) {
				TankAimComponent->Fire();
			}
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);

	if (InPawn) {
		ATank* Tank = Cast<ATank>(InPawn);
		if (Tank) {
			Tank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
		}
	}
}

void ATankAIController::OnDeath() {
	UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *GetPawn()->GetName());
	GetPawn()->DetachFromControllerPendingDestroy();
}