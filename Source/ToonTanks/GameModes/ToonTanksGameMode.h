// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);

private:
	void HandleGameStart();
	void HandleGameOver(bool bPlayerWon);

	int32 GetTargetTurretCount();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")

	int32 StartDelay = 3;
	
private:
	APlayerControllerBase* PlayerControllerRef;
	
	APawnTank* PlayerTank;

	int32 TargetTurretsCount = 0;
};
