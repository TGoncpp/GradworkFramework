// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Logger.generated.h"

/**
 * 
 */
UCLASS()
class GRADWORK_NPCAI_API ULogger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void LogValuesOnTime(float time, float loggedValue, const FString& logInformation);
	UFUNCTION(BlueprintCallable)
	static void LogWinLose(int win, int loss, const FString& logInformation);
	
};
