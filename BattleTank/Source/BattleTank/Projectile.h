// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Launch(float Speed);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Explosion;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly)
	float DestroyDelaySeconds = 5;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10;

private:
	UProjectileMovementComponent* MovementComponent = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpired();
};
