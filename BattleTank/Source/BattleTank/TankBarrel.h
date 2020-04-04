// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float MinimumAngle = 0.0;

	UPROPERTY(EditAnywhere)
	float MaxiumAngle = 90.0;

	UPROPERTY(EditAnywhere)
	float VerticalSpeed = 20.0;

	void Elevate(float Degrees);
};
