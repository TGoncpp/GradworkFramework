#include "GOAPGoalBase.h"
//#include "WorldStateActor.h"

GOAPGoalBase::GOAPGoalBase()
{
}

GOAPGoalBase::~GOAPGoalBase()
{
}

AWorldStateActor* GOAPGoalBase::GetDesiredState() const
{
	return m_DesiredState;
}

FString GOAPGoalBase::GetGoalName() const
{
	if (M_NameOfGoal.IsEmpty())
		return "NoName";
	return M_NameOfGoal;
}
