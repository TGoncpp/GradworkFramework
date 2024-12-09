#pragma once

#include "CoreMinimal.h"
#include "WorldStateActor.h"

//class AWorldStateActor;
enum class EAction : uint8;
class BlackBoard;

class GRADWORK_NPCAI_API GOAPActionBase
{
public:
	GOAPActionBase();
	virtual ~GOAPActionBase();
	//virtual bool IsVallid() const = 0;
	virtual bool IsFinished()const = 0;
	virtual void UpdateAction(BlackBoard* blackboard) = 0;
	virtual EAction GetActionInput()const = 0;

	float GetActionScore()const;
	AWorldStateActor* GetDesiredState()const;
	bool DoesActionSatisfyGoal(AWorldStateActor* desiredState)const;
	bool DoesActionSatisfyActionState(AWorldStateActor* desiredState, int indexOfWorldState)const;

protected:
	AWorldStateActor* m_DesiredState = nullptr;
	AWorldStateActor* m_SatisfiesState = nullptr;
	float m_Cost = 0.0f;
	float m_Heuristic = 0.0f;
};
