// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackNew;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	void IntendMoveForward(float Throw);
	void IntendMoveRight(float Throw);

	UFUNCTION(BlueprintCallable)
	void SetTrackReferences(UTankTrackNew* LeftTrackToSet, UTankTrackNew* RighTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrackNew* LeftTrack;
	UTankTrackNew* RightTrack;
};
