// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	if (GetTank()) {
		UE_LOG(LogTemp, Warning, TEXT("AI Possessing tank %s"), *GetTank()->GetName())
	}

	if (GetPlayerTank()) {
		UE_LOG(LogTemp, Warning, TEXT("Player tank by AI is %s"), *GetPlayerTank()->GetName())
	}
}

ATank* ATankAIController::GetTank() {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() {
	return GetPlayerController()->GetTank();
}

ATankPlayerController* ATankAIController::GetPlayerController() {
	return Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
}