// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrackNew.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::SetTrackReferences(UTankTrackNew* LeftTrackToSet, UTankTrackNew* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto RequestedDirection = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(GetOwner()->GetActorForwardVector(), RequestedDirection);
	IntendMoveForward(ForwardThrow);

	auto RightTurnThrow = FVector::CrossProduct(GetOwner()->GetActorForwardVector(), RequestedDirection).Z;
	IntendMoveRight(RightTurnThrow);
}