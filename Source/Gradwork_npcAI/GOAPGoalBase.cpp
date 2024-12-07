#include "GOAPGoalBase.h"
#include "WorldStateActor.h"

GOAPGoalBase::GOAPGoalBase()
{
}

GOAPGoalBase::~GOAPGoalBase()
{
}

AWorldStateActor* GOAPGoalBase::GetDesiredState() const
{
	return m_DiseredState;
}
