#pragma once

#include "CoreMinimal.h"

class WorldState;

class GRADWORK_NPCAI_API GOAPGoalBase
{
public:
	GOAPGoalBase();
	virtual ~GOAPGoalBase();

	virtual bool IsVallid() const = 0;

protected:
	WorldState* m_DiseredState = nullptr;
	FString M_NameOfGoal{ "defaultGoal" };
};
