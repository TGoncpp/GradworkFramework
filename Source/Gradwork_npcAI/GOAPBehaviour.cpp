#include "GOAPBehaviour.h"
//#include "GOAPActionBase.h"
//#include "GOAPGoalBase.h"
//#include "WorldStateActor.h"


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
	UpdateCurrentWorldState();
}

EAction AGOAPBehaviour::Execute(FVector2D& moveInput)
{
	if (m_CurrentPlan.IsEmpty())
		CreateNewPlan();

	//if creating plan fails return idle
	if (m_CurrentPlan.IsEmpty())
		return EAction::Idle;

	if (!m_CurrentAction || m_CurrentAction->IsFinished() )
		m_CurrentAction = m_CurrentPlan.Pop();
	else
		m_CurrentAction->UpdateAction(m_BlackboardRef);

	return m_CurrentAction->GetActionInput();

}

void AGOAPBehaviour::CreateNewPlan()
{
	m_CurrentGoal = SelectFirstVallidPriorityGoal();

	//Find the lowest scoring Action that satisfies the goal's desired state
	GOAPActionBase* startAction = FindStartAction();
		
	//Looks recursively for all the actions needed to achieve the current goal
	if (startAction)
		FindAllNeccesaryGOAPActions(startAction);

}

GOAPGoalBase* AGOAPBehaviour::SelectFirstVallidPriorityGoal()
{
	for (const auto& goal : m_AllGOAPGoals)
	{
		if (goal->IsVallid(m_BlackboardRef))
			return goal;
	}
	return nullptr;
}

void AGOAPBehaviour::UpdateCurrentWorldState()
{
	
}

GOAPActionBase* AGOAPBehaviour::FindStartAction()
{
	//compare currentWorldState with the desiredworldState off the goal
	AWorldStateActor* desiredState = m_CurrentGoal->GetDesiredState();
	ComparedWorldState->ResetWorldState();
	desiredState->CompareWithCurrentState(CurrentWorldState, ComparedWorldState);

	//find the lowest scoring action based from the compared DesiredworldState
	GOAPActionBase* possibleAction = nullptr;
	float lowestScore = 0.0f;
	for (const auto& action : m_AllGOAPActions)
	{
		if (action->DoesActionSatisfyGoal(ComparedWorldState) && action->GetActionScore() < lowestScore)
		{
			possibleAction = action;
			lowestScore = action->GetActionScore();
		}
	}
	return possibleAction;
}

void AGOAPBehaviour::FindAllNeccesaryGOAPActions(GOAPActionBase* startAction)
{
	//compare currentWorldState with the desiredworldState off the goal
	AWorldStateActor* currentDesiredWorldState = startAction->GetDesiredState();
	ComparedWorldState->ResetWorldState();
	currentDesiredWorldState->CompareWithCurrentState(CurrentWorldState, ComparedWorldState);

	int numOffStatesToSatisfy = ComparedWorldState->GetNumOffUnsatisfiedStates();

	//return out off recursion if no more actions to find
	if (numOffStatesToSatisfy == 0)
		return;

	//every action can have multiple states to satisfy, first it will create a plan for the first one 
	//the last plan is the one that will be executed first 
	for (int index{ 0 }; index < ComparedWorldState->GetNumOffAllStates(); index++)
	{
		//look at next one if current state in worldstate is not active
		if (ComparedWorldState->IsWorldStateActiveAtIndex(index))
			continue;

		//loop over all actions to find the lowest scoring action that satisfies current desired state
		float score = 0.0f;
		GOAPActionBase* bestAction = nullptr;
		for (const auto& action: m_AllGOAPActions)
		{
			
			if (action->DoesActionSatisfyActionState(ComparedWorldState, index))
			{
				float newScore = action->GetActionScore();
				if (newScore < score)
				{
					score = newScore;
					bestAction = action;
				}
			}
		}
		m_CurrentPlan.Add(bestAction);

		//recursively look for more actions to add if current bestAction has more desiredState.
		FindAllNeccesaryGOAPActions(bestAction);

	}

}

void AGOAPBehaviour::AddGOAPGoal(AGOAPGoal* newGoal)
{
	m_AllGOAPGoals.Add(newGoal);
}

void AGOAPBehaviour::AddGOAPAction(AGOAPAction* newAction)
{
	m_AllGOAPActions.Add(newAction);
}

//AWorldStateActor* AGOAPBehaviour::GetCurrentState()
//{
//	return CurrentWorldState;
//}

