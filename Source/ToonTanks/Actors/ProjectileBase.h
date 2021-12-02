// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class AProjectileBase;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;
	
	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category= "Effects")
	TSubclassOf<UCameraShake> HitShake;
	
	UPROPERTY(EditAnywhere, Category= "Effects")
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category= "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category= "Effects")
	USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Move", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;
};
