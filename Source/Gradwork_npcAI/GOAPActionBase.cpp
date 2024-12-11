#include "GOAPActionBase.h"
//#include "WorldStateActor.h"


GOAPActionBase::GOAPActionBase()
{
}

GOAPActionBase::~GOAPActionBase()
{
}

float GOAPActionBase::GetActionScore(AWorldStateActor* currentWorldState) const
{
	
	return CalculateHeuristic(currentWorldState) + m_Cost;
}

AWorldStateActor* GOAPActionBase::GetDesiredState() const
{
	return m_DesiredState;
}

bool GOAPActionBase::DoesActionSatisfyGoal(AWorldStateActor* desiredState)const
{
	return desiredState->GetGoalState() == m_SatisfiesState->GetGoalState() && m_SatisfiesState->IsWorldStateActiveAtIndex(0);
}

bool GOAPActionBase::DoesActionSatisfyActionState(AWorldStateActor* desiredState, int indexOfWorldState)const
{
	return m_SatisfiesState->GetIndexOffAllActiveStates().Contains(indexOfWorldState) 
		&& m_SatisfiesState->IsWorldStateEqualOnIndex(desiredState, indexOfWorldState);
}

float GOAPActionBase::CalculateHeuristic(AWorldStateActor* currentWorldState) const
{
	//get result from the compared state and then reset the state so it will be usable for others
	m_DesiredState->CompareWithCurrentState(currentWorldState, m_ComparedWorldState);
	float result = m_ComparedWorldState->GetNumOffUnsatisfiedStates();
	m_ComparedWorldState->ResetWorldState();
	return result;
}
