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

enum class EGoal : uint8
{
	Fight UMETA(DisplayName = "Fight"),
	Dodge UMETA(DisplayName = "Dodge"),
	Heal UMETA(DisplayName = "Heal"),
	Counter UMETA(DisplayName = "Heal"),
	
};



class GRADWORK_NPCAI_API WorldState
{
public:
	WorldState();
	~WorldState();

	int GetNumOffUnsatisfiedStates()const;
	TArray<int> GetIndexOffAllActiveStates()const;
	void UpdateWorldState(WorldState* WorldState);
	EGoal GetGoalState()const;
	EAction GetActionState()const;
	EAction GetOpponentActionState()const;
	ECondition GetConditionState()const;
	ECondition GetOpponentConditionState()const;
	EDistance GetDistanceState()const;
	bool IsWorldStateEqualOnIndex(WorldState* otherWorldState, int index)const;

private:
	TArray<bool> m_IsSatisfiedWorldStates;
	EGoal m_GoalState;                  //index =0 -> will always be the desired state off a Goal
	EAction m_ActionState;              //index =1
	EAction m_OpponentActionState;      //index =2
	ECondition m_ConditionState;        //index =3
	ECondition m_OpponentConditionState;//index =4
	EDistance m_DistanceToOpponentState;//index =5
};
