// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBase.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleCollider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh Component"));
	BaseMesh->SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh Component"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent =  CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(const FVector LookAtTarget) const
{
	const FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	const FVector StartLocation = TurretMesh->GetComponentLocation();
	const FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();

	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if (Projectile_BP)
	{
		const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile_BP, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
}
