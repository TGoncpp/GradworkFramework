#include "GOAPGoalBase.h"
//#include "WorldState.h"

GOAPGoalBase::GOAPGoalBase()
{
}

GOAPGoalBase::~GOAPGoalBase()
{
}

WorldState* GOAPGoalBase::GetDisiredState() const
{
	return m_DiseredState.Get();
}
