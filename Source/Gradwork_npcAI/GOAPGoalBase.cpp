#include "GOAPGoalBase.h"
#include "WorldStateActor.h"

GOAPGoalBase::GOAPGoalBase()
{
}

GOAPGoalBase::~GOAPGoalBase()
{
}

AWorldStateActor* GOAPGoalBase::GetDisiredState() const
{
	return m_DiseredState;
}
