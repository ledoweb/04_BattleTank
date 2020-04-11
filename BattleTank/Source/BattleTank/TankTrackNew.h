// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackNew.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackNew : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	UTankTrackNew();

	void ApplySidewaysForce(float DeltaTime);
	
public:
	UPROPERTY(EditDefaultsOnly)
	float MaxThrottle = 20000000;

	void SetThrottle(float Throttle);
	void ApplyThrottle();
	float CurrentThrottle = 0;

private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
