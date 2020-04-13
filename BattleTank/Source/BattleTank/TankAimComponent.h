// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EAimState : uint8 {
	Locked, Aiming, Reloading, OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector WorldSpaceCoordinate);
	void MoveBarrelTowards(FVector AimDirection);
	void Fire();

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	UPROPERTY(BlueprintReadOnly)
	EAimState AimState = EAimState::Aiming;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 10000.0;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 2;

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(BlueprintReadOnly)
	int Rounds = 10;

private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
};
