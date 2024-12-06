#include "GOAPActionBase.h"
//#include "WorldState.h"


GOAPActionBase::GOAPActionBase()
{
}

GOAPActionBase::~GOAPActionBase()
{
}

float GOAPActionBase::GetActionScore() const
{
	return m_Heuristic + m_Cost;
}

WorldState* GOAPActionBase::GetDisiredState() const
{
	return m_DiseredState.Get();
}

bool GOAPActionBase::DoesActionSatisfyGoal(WorldState* desiredState)
{
	return desiredState->GetGoalState() == m_SatisfiesState->GetGoalState();
}

bool GOAPActionBase::DoesActionSatisfyActionState(WorldState* desiredState, int indexOfWorldState)
{
	return m_SatisfiesState->GetIndexOffAllActiveStates().Contains(indexOfWorldState) 
		&& m_SatisfiesState->IsWorldStateEqualOnIndex(desiredState, indexOfWorldState);
}
