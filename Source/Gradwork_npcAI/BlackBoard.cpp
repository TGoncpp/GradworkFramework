// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard.h"

BlackBoard::BlackBoard()
{
	//m_KeyValues = TMap<FString, float>();
	m_KeyValues.Empty();
	m_KeyValues.Reserve(10);
}

BlackBoard::~BlackBoard()
{
	m_KeyValues.Empty();
}

void BlackBoard::AddBlackboardValue(const FString& key, float value)
{
	//m_KeyValues.Add(TEXT("key"), value);//-> WHY DOES THIS CRASH? DOESNT MAKE ANY SENSE!!!!
	//m_KeyValues[key] = value;
	m_KeyValues.Add(BlackboardValue{ key, value });
}

void BlackBoard::UpdateKey(const FString& key, float value)
{
	for (auto& keyValue : m_KeyValues)
	{
		if (keyValue.key == key)
		{
			keyValue.value = value;
			return;
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("this keyvalue was not found with UpdateKey in blackboard!")));

	/*if (m_KeyValues.Contains(key))
		m_KeyValues[key] = value;
	else*/
}

float BlackBoard::GetKeyValue(const FString& key) const
{
	for (auto& keyValue : m_KeyValues)
	{
		if (keyValue.key == key)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("!!!!!!!!!!!!!!!!!!!!!!!!key found blackboard!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")));
			return keyValue.value;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("!!!!!!!!!!!!!!!!!!!!!!!!key not found in blackboard!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")));
	return 0.0f;
}
