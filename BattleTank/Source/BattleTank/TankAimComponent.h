// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EAimState : uint8 {
	Locked, Aiming, Reloading
};

class UTankBarrel;
class UTankTurret;

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
	void AimAt(FVector WorldSpaceCoordinate, float ProjectileSpeed);
	void SetBarrelComponent(UTankBarrel* BarrelComponent);
	void SetTurretComponent(UTankTurret* TurretComponent);
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(BlueprintReadOnly)
	EAimState AimState = EAimState::Reloading;

private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
};
