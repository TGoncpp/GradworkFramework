#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"

class WorldState;
enum class EAction : uint8;


class GRADWORK_NPCAI_API GOAPActionBase
{
public:
	GOAPActionBase();
	virtual ~GOAPActionBase();
	virtual bool IsVallid() const = 0;
	virtual bool IsFinished() const = 0;
	virtual void UpdateAction() const = 0;
	virtual EAction GetActionInput() const = 0;

	float GetActionScore()const;
	WorldState* GetDisiredState()const;
	bool DoesActionSatisfyGoal(WorldState* desiredState);
	bool DoesActionSatisfyActionState(WorldState* desiredState, int indexOfWorldState);

protected:
	TUniquePtr<WorldState> m_DiseredState = nullptr;
	TUniquePtr<WorldState> m_SatisfiesState = nullptr;
	FString M_NameOfAction{ "defaultAction" };
	float m_Cost = 0.0f;
	float m_Heuristic = 0.0f;
};
