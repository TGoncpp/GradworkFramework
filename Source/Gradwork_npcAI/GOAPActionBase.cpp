#include "GOAPActionBase.h"
#include "WorldStateActor.h"


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

AWorldStateActor* GOAPActionBase::GetDesiredState() const
{
	return m_DiseredState;
}

bool GOAPActionBase::DoesActionSatisfyGoal(AWorldStateActor* desiredState)const
{
	return desiredState->GetGoalState() == m_SatisfiesState->GetGoalState();
}

bool GOAPActionBase::DoesActionSatisfyActionState(AWorldStateActor* desiredState, int indexOfWorldState)const
{
	return m_SatisfiesState->GetIndexOffAllActiveStates().Contains(indexOfWorldState) 
		&& m_SatisfiesState->IsWorldStateEqualOnIndex(desiredState, indexOfWorldState);
}
