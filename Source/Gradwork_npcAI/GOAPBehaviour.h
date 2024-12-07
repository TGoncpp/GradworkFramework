#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"
#include "AIBehaviourBase.h"
//#include "WorldState.h"
//#include "GOAPGoalBase.h"
//#include "GOAPActionBase.h"

#include "GOAPBehaviour.generated.h"

class GOAPActionBase; 
class GOAPGoalBase;
class AWorldStateActor;

UCLASS()
class GRADWORK_NPCAI_API AGOAPBehaviour : public AActor, public AIBehaviourBase
{
	GENERATED_BODY()
	
public:	
	AGOAPBehaviour();
	virtual void Tick(float DeltaTime) override;

	virtual EAction Execute(FVector2D& moveInput)override;


protected:
	virtual void BeginPlay() override;
	void AddGOAPGoal(GOAPGoalBase* newGoal);
	void AddGOAPAction(GOAPActionBase* newAction);

private:	
	GOAPActionBase* FindStartAction();
	void CreateNewPlan();
	void FindAllNeccesaryGOAPActions(GOAPActionBase* startAction);
	GOAPGoalBase* SelectFirstVallidPriorityGoal();

	TArray < GOAPActionBase* >  m_AllGOAPActions;
	TArray < GOAPGoalBase* >  m_AllGOAPGoals;
	TArray<GOAPActionBase*> m_CurrentPlan;
	AWorldStateActor* m_CurrentWorldState = nullptr;
	GOAPGoalBase* m_CurrentGoal = nullptr;
	GOAPActionBase* m_CurrentAction = nullptr;

};
