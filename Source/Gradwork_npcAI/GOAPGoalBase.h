#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"

class WorldState;

class GRADWORK_NPCAI_API GOAPGoalBase
{
public:
	GOAPGoalBase();
	virtual ~GOAPGoalBase();

	virtual bool IsVallid() const = 0;
	WorldState* GetDisiredState()const;


protected:
	TUniquePtr<WorldState> m_DiseredState = nullptr;
	FString M_NameOfGoal{ "defaultGoal" };
};
