// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Components/SceneComponent.h"
#include "TankCameraManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankCameraManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankCameraManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
	FComponentReference SpringArmComponentReference;

	UPROPERTY(EditAnywhere)
	FComponentReference AzimuthGimbalComponentReference;

private:
	void UpdateCameraAzimuth(float Movement);
	void UpdateCameraElevation(float Movement);
	
	UInputComponent* InputComponent;
	
	UPROPERTY(EditAnywhere)
	float CameraSpeedAzimuth = 10.0f;

	UPROPERTY(EditAnywhere)
	float CameraSpeedElevation = 10.0f;

	USpringArmComponent* SpringArm;
	USceneComponent* AzimuthGimbal;
};
