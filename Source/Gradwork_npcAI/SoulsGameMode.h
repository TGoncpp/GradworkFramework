// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"

#include "SoulsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRADWORK_NPCAI_API ASoulsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameMode")
	float GetSettedGameTime()const;
	
protected:
	virtual void BeginPlay()override;

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void CreateHud();
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void LogWinLoss();

	void StartGame();

	UPROPERTY(EditAnywhere, Category = "GameMode")
	float TimeToFinish = 300.0f;

private:
	void PauseGame();

	FTimerHandle m_Timer;
};
