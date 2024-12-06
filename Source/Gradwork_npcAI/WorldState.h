#pragma once

#include "CoreMinimal.h"

enum class EAction : uint8;

enum class ECondition : uint8
{
	Perfect UMETA(DisplayName = "Perfect"),
	LowHP UMETA(DisplayName = "LowHP"),
	LowSP UMETA(DisplayName = "LowSP"),
	Low UMETA(DisplayName = "Low"),
	
};

enum class EDistance : uint8
{
	Close UMETA(DisplayName = "Close"),
	OutOfRange UMETA(DisplayName = "OutOfRange"),
	HealDistance UMETA(DisplayName = "HealDistance"),
	
};


class GRADWORK_NPCAI_API WorldState
{
public:
	WorldState();
	~WorldState();

	int GetNumOffUnsatisfiedStates()const;
	void UpdateWorldState(WorldState* WorldState);

private:
	TArray<bool> m_IsSatisfiedWorldStates;
	EAction m_ActionState;
	EAction m_OpponentActionState;
	ECondition m_ConditionState;
	ECondition m_OpponentConditionState;
	EDistance m_DistanceToOpponent;
};
