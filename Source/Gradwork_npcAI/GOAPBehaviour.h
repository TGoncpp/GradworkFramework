#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"
#include "AIBehaviourBase.h"
#include "GOAPGoalBase.h"
#include "GOAPActionBase.h"

#include "GOAPBehaviour.generated.h"


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

private:	
	void CreateNewPlan();
	void FindAllNeccesaryGOAPActions();
	GOAPGoalBase* SelectFirstVallidPriorityGoal();

	TArray <TUniquePtr< GOAPActionBase > > m_AllGOAPActions;
	TArray <TUniquePtr< GOAPGoalBase > > m_AllGOAPGoals;
	TArray<GOAPActionBase*> m_CurrentPlan;
	TUniquePtr <WorldState> m_CurrentWorldState = nullptr;
	GOAPGoalBase* m_CurrentGoal = nullptr;
	GOAPActionBase* m_CurrentAction = nullptr;

};
