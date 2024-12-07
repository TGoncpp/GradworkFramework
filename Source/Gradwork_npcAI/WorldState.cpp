#include "WorldState.h"

WorldState::WorldState()
{
}

WorldState::~WorldState()
{
}

//int WorldState::GetNumOffUnsatisfiedStates() const
//{
//	int numOffUnsatisfiedStates = 0;
//	for (const bool& worldState : m_IsActiveWorldStates)
//	{
//		if (worldState)
//			numOffUnsatisfiedStates++;
//	}
//
//	return numOffUnsatisfiedStates;
//}
//
//int WorldState::GetNumOffAllStates() const
//{
//	return m_IsActiveWorldStates.Num();
//}
//
//TArray<int> WorldState::GetIndexOffAllActiveStates() const
//{
//	TArray<int> indexes;
//	for (int index{}; index < m_IsActiveWorldStates.Num(); index++)
//	{
//		if (m_IsActiveWorldStates[index])
//			indexes.Add(index);
//	}
//	return indexes;
//}
//
//void WorldState::UpdateWorldState(WorldState* WorldState)
//{
//
//}
//
//EGoal WorldState::GetGoalState() const
//{
//	return m_GoalState;
//}
//
//EAction WorldState::GetActionState() const
//{
//	return m_ActionState;
//}
//
//EAction WorldState::GetOpponentActionState() const
//{
//	return m_OpponentActionState;
//}
//
//ECondition WorldState::GetConditionState() const
//{
//	return m_ConditionState;
//}
//
//ECondition WorldState::GetOpponentConditionState() const
//{
//	return m_OpponentConditionState;
//}
//
//EDistance WorldState::GetDistanceState() const
//{
//	return m_DistanceToOpponentState;
//}
//
//bool WorldState::IsWorldStateEqualOnIndex(WorldState* otherWorldState, int index) const
//{
//	switch (index)
//	{
//	case 0:
//		return m_GoalState == otherWorldState->GetGoalState();
//	case 1:
//		return m_ActionState == otherWorldState->GetActionState();
//	case 2:
//		return m_OpponentActionState == otherWorldState->GetOpponentActionState();
//	case 3:
//		return m_ConditionState == otherWorldState->GetConditionState();
//	case 4:
//		return m_OpponentConditionState == otherWorldState->GetOpponentConditionState();
//	case 5:
//		return m_DistanceToOpponentState == otherWorldState->GetDistanceState();
//	}
//	return false;
//}
//
//bool WorldState::IsWorldStateActiveAtIndex(int index) const
//{
//	return m_IsActiveWorldStates[index];
//}
