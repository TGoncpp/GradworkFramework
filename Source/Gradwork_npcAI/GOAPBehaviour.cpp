#include "GOAPBehaviour.h"
//#include "GOAPActionBase.h"
//#include "GOAPGoalBase.h"


// Sets default values
AGOAPBehaviour::AGOAPBehaviour()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGOAPBehaviour::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGOAPBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EAction AGOAPBehaviour::Execute(FVector2D& moveInput)
{
	if (m_CurrentPlan.IsEmpty())
		CreateNewPlan();
	

	if (!m_CurrentAction || m_CurrentAction->IsFinished())
		m_CurrentAction = m_CurrentPlan.Pop();

	return m_CurrentAction->GetActionInput();

}

GOAPActionBase* AGOAPBehaviour::FindStartAction()
{
	WorldState* desiredState = m_CurrentGoal->GetDisiredState();

	GOAPActionBase* possibleAction = nullptr;
	float lowestScore = 0.0f;
	for (const auto& action : m_AllGOAPActions)
	{
		if (action->DoesActionSatisfyGoal(desiredState) && action->GetActionScore() < lowestScore)
		{
			possibleAction = action.Get();
			lowestScore = action->GetActionScore();
		}
	}
	return possibleAction;
}

void AGOAPBehaviour::CreateNewPlan()
{
	m_CurrentGoal = SelectFirstVallidPriorityGoal();

	//Find the lowest scoring Action that satisfies the goal desired state
	GOAPActionBase* startAction = FindStartAction();
		
	//Looks recursively for all the actions needed to achieve the current goal
	FindAllNeccesaryGOAPActions(startAction);

}

void AGOAPBehaviour::FindAllNeccesaryGOAPActions(GOAPActionBase* startAction)
{

}

GOAPGoalBase* AGOAPBehaviour::SelectFirstVallidPriorityGoal()
{
	for (const auto& goal : m_AllGOAPGoals)
	{
		if (goal.IsValid())
			return goal.Get();
	}
	return nullptr;
}

