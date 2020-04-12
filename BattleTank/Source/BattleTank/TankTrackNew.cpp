// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrackNew.h"

UTankTrackNew::UTankTrackNew()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackNew::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrackNew::OnHit);
}

void UTankTrackNew::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"))
	ApplySidewaysForce(GetWorld()->DeltaTimeSeconds);
	ApplyThrottle();
	CurrentThrottle = 0.0;
}

void UTankTrackNew::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrackNew::ApplyThrottle()
{
	auto ForceVector = GetForwardVector() * MaxThrottle * CurrentThrottle;
	auto Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Root->AddForceAtLocation(ForceVector, GetComponentLocation());

	//UE_LOG(LogTemp, Warning, TEXT("%s: Setting throttle %s at %s"), *GetName(), *ForceVector.ToString(), *GetComponentLocation().ToString())
}

void UTankTrackNew::ApplySidewaysForce(float DeltaTime)
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}
