// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion"));
	Explosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Explosion->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float Speed) {
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	Explosion->Activate();
}

