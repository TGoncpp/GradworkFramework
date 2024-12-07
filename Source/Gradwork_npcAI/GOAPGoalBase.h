#pragma once

#include "CoreMinimal.h"

class AWorldStateActor;
class BlackBoard;

class GRADWORK_NPCAI_API GOAPGoalBase
{
public:
	GOAPGoalBase();
	virtual ~GOAPGoalBase();

	virtual bool IsVallid(BlackBoard* blackboard)const = 0;
	AWorldStateActor* GetDesiredState()const;


protected:
	AWorldStateActor* m_DiseredState = nullptr;
	FString M_NameOfGoal{ "defaultGoal" };
};
