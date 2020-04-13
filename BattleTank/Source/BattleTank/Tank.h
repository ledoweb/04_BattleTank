// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankTrackNew;
class UTankMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	UPROPERTY(BlueprintReadWrite)
	UTankAimComponent* TankAimComponent = nullptr;
	UTankTrackNew* LeftTrack = nullptr;
	UTankTrackNew* RightTrack = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UTankMovementComponent* TankMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 StartHealth;

	int32 Health;

	FOnDeath OnDeath;
private:
	void SetTrackReferences();
};
