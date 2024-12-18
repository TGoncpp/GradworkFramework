#pragma once

#include "CoreMinimal.h"
#include "WorldStateActor.h"

//class AWorldStateActor;
class BlackBoard;

class GRADWORK_NPCAI_API GOAPGoalBase
{
public:
	GOAPGoalBase();
	virtual ~GOAPGoalBase();

	virtual bool IsVallid(BlackBoard* blackboard)const = 0;
	AWorldStateActor* GetDesiredState()const;
	FString GetGoalName()const;

protected:
	AWorldStateActor* m_DesiredState = nullptr;
	FString M_NameOfGoal{ "defaultGoal" };
};
