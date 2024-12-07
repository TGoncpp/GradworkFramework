#pragma once

#include "CoreMinimal.h"

class AWorldStateActor;

class GRADWORK_NPCAI_API GOAPGoalBase
{
public:
	GOAPGoalBase();
	virtual ~GOAPGoalBase();

	virtual bool IsVallid() const = 0;
	AWorldStateActor* GetDisiredState()const;


protected:
	AWorldStateActor* m_DiseredState = nullptr;
	FString M_NameOfGoal{ "defaultGoal" };
};
