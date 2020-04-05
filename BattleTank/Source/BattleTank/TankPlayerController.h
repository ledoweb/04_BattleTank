// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	ATank* GetTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	bool GetAimHitLocation(FVector& result, FVector direction);
	bool GetAimPointWorldDirection(FVector& direction);

	UPROPERTY(EditAnywhere)
	float AimDistance = 10000.0;

	UPROPERTY(EditAnywhere)
	float CrosshairPositionX = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairPositionY = 0.3333;
};