// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrackNew;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankBarrelComponent(UTankBarrel* BarrelComponent);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankTurretComponent(UTankTurret* TurretComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AimAt(FVector WorldSpaceCoordinate);
	void Fire();

	UTankAimComponent* TankAimComponent = nullptr;
	UTankBarrel* TankBarrel = nullptr;
	UTankTrackNew* LeftTrack = nullptr;
	UTankTrackNew* RightTrack = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 10000.0;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3;

	double LastFireTime = 0;
private:
	void SetTrackReferences();
};
