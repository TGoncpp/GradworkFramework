
#include "AIBehaviourBase.h"


AIBehaviourBase::AIBehaviourBase()
{
}

AIBehaviourBase::~AIBehaviourBase()
{
}

void AIBehaviourBase::AddBlackboardRefrence(BlackBoard* blackboardRef)
{
	m_BlackboardRef = blackboardRef;
}
