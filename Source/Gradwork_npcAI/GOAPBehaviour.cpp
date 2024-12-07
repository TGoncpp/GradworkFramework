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
	else
		m_CurrentAction->UpdateAction();

	return m_CurrentAction->GetActionInput();

}

void AGOAPBehaviour::CreateNewPlan()
{
	m_CurrentGoal = SelectFirstVallidPriorityGoal();

	//Find the lowest scoring Action that satisfies the goal's desired state
	GOAPActionBase* startAction = FindStartAction();
		
	//Looks recursively for all the actions needed to achieve the current goal
	FindAllNeccesaryGOAPActions(startAction);

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

void AGOAPBehaviour::FindAllNeccesaryGOAPActions(GOAPActionBase* startAction)
{
	WorldState* currentDesiredWorldState = startAction->GetDisiredState();
	int numOffStatesToSatisfy = currentDesiredWorldState->GetNumOffUnsatisfiedStates();

	//return out off recursion if no more actions to find
	if (numOffStatesToSatisfy == 0)
		return;

	//every action can have multiple states to satisfy, first it will create a plan for the first one 
	//the last plan is the one that will be executed first 
	for (int index{ 0 }; index < currentDesiredWorldState->GetNumOffAllStates(); index++)
	{
		//look at next one if current state in worldstate is not active
		if (currentDesiredWorldState->IsWorldStateActiveAtIndex(index))
			continue;

		//loop over all actions to find the lowest scoring action that satisfies current desired state
		float score = 0.0f;
		GOAPActionBase* bestAction = nullptr;
		for (const auto& action: m_AllGOAPActions)
		{
			
			if (action->DoesActionSatisfyActionState(currentDesiredWorldState, index))
			{
				if (action->GetActionScore() < score)
				{
					score = action->GetActionScore();
					bestAction = action.Get();
				}
			}
		}
		m_CurrentPlan.Add(bestAction);

		//recursively look for more actions to add if current bestAction has more desiredState.
		FindAllNeccesaryGOAPActions(bestAction);

	}

}

