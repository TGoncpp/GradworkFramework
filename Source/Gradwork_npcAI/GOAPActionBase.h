#pragma once

#include "CoreMinimal.h"

class WorldState;

class GRADWORK_NPCAI_API GOAPActionBase
{
public:
	GOAPActionBase();
	virtual ~GOAPActionBase();
	virtual bool IsVallid() const = 0;

protected:
	WorldState* m_DiseredState = nullptr;
	FString M_NameOfAction{ "defaultAction" };
};
