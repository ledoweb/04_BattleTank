// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrackNew.h"


void UTankTrackNew::SetThrottle(float Throttle) {
	
	auto ForceVector = GetForwardVector() * MaxThrottle * Throttle;
	auto Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Root->AddForceAtLocation(ForceVector, GetComponentLocation());

	UE_LOG(LogTemp, Warning, TEXT("%s: Setting throttle %s at %s"), *GetName(), *ForceVector.ToString(), *GetComponentLocation().ToString())
}