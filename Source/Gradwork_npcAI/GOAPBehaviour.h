#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"
#include "AIBehaviourBase.h"
//#include "WorldState.h"
#include "GOAPGoal.h"
#include "GOAPAction.h"

#include "GOAPBehaviour.generated.h"

//class GOAPActionBase; 
//class GOAPGoalBase;
//class AWorldStateActor;

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
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	void AddGOAPGoal(AGOAPGoal* newGoal);
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	void AddGOAPAction(AGOAPAction* newAction);
	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GOAP")
	//AWorldStateActor* GetCurrentState();

	UPROPERTY(BlueprintReadWrite, Category = "GOAP")
	AWorldStateActor* CurrentWorldState = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "GOAP")
	AWorldStateActor* ComparedWorldState = nullptr;
	//Make the plan and all actions visible in editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GOAP")
	TArray < AGOAPAction* >  m_AllGOAPActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GOAP")
	TArray<AGOAPAction*> m_CurrentPlan;

private:	
	AGOAPAction* FindStartAction();
	void CreateNewPlan();
	void FindAllNeccesaryGOAPActions(GOAPActionBase* startAction);
	GOAPGoalBase* SelectFirstVallidPriorityGoal();
	void UpdateCurrentWorldState();
	bool CurrentGoalInvallid();

	TArray < GOAPGoalBase* >  m_AllGOAPGoals;
	GOAPGoalBase* m_CurrentGoal = nullptr;
	AGOAPAction* m_CurrentAction = nullptr;

};
