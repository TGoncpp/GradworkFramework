// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoulsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRADWORK_NPCAI_API ASoulsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay()override;
};
