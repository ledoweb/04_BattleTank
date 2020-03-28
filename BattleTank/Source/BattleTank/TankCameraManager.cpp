// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankCameraManager.h"

// Sets default values for this component's properties
UTankCameraManager::UTankCameraManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankCameraManager::BeginPlay()
{
	Super::BeginPlay();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	//SpringArm = (USpringArmComponent*)SpringArmComponentReference.GetComponent(GetOwner());
	//AzimuthGimbal = (USceneComponent*)AzimuthGimbalComponentReference.GetComponent(GetOwner());
	SpringArm = GetOwner()->FindComponentByClass<USpringArmComponent>();
	AzimuthGimbal = Cast<USceneComponent>(GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), "AzimuthGimbal")[0]);

	if (InputComponent != nullptr) {
		InputComponent->BindAxis("TankCamera_Azimuth", this, &UTankCameraManager::UpdateCameraAzimuth);
		InputComponent->BindAxis("TankCamera_Elevation", this, &UTankCameraManager::UpdateCameraElevation);
	}
	// ...
	
}


// Called every frame
void UTankCameraManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankCameraManager::UpdateCameraAzimuth(float Movement) {
	if (AzimuthGimbal != nullptr) {
		AzimuthGimbal->AddLocalRotation(FRotator(0, Movement * CameraSpeedAzimuth, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AzimuthGimbal component is null"))
	}
}

void UTankCameraManager::UpdateCameraElevation(float Movement) {
	if (SpringArm != nullptr) {
		SpringArm->AddLocalRotation(FRotator(Movement * CameraSpeedAzimuth, 0, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SpringArm component is null"))
	}
}

