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
	return false;
}

bool GOAPActionBase::DoesActionSatisfyActionState(WorldState* desiredState, int indexOfWorldState)
{
	return false;
}
