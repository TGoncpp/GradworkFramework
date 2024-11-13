// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct BlackboardValue
{
	FString key;
	float value;
};

class GRADWORK_NPCAI_API BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();

	void AddBlackboardValue(const FString& key, float value);
	void UpdateKey(const FString& key, float value);
	float GetKeyValue(const FString& key) const;

private:
	TArray< BlackboardValue> m_KeyValues;
	//TMap<FString, float> m_KeyValues;
	//TMap<FString, float> m_Health;
	//TMap<FString, float> m_EnemyHealth;
	//TMap<FString, float> m_Stamina;
	//TMap<FString, float> m_EnemyStamina;
	//TMap<FString, float> m_EnemyDistance;
	//TMap<FString, float> m_EnemyIsBlocking;
	//TMap<FString, float> m_EnemyIsHealing;
};
