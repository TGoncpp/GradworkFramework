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
	//Start a new plan if current goal takes to long or gets invallid
	if (CurrentGoalInvallid())
	{
		m_CurrentPlan.Empty();
		m_CurrentAction = nullptr;
	}
	
	if (m_CurrentPlan.IsEmpty())
		CreateNewPlan();

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("size off plan: %i"), m_CurrentPlan.Num()));
	//if creating plan fails return idle
	if (m_CurrentPlan.IsEmpty())
		return EAction::Idle;

	if (!m_CurrentAction || m_CurrentAction->IsFinished() )
	{
		m_CurrentAction = m_CurrentPlan.Pop();
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("current action is vallid: %i"), m_CurrentAction != nullptr));

	}
	else
		m_CurrentAction->UpdateAction(m_BlackboardRef);

	return m_CurrentAction->GetActionInput();

}

void AGOAPBehaviour::CreateNewPlan()
{
	//reset the timer off previous goal
	if (m_CurrentGoal)
		m_CurrentGoal->StartTimer(false);

	//take the first available goal in list. ordered by priority in array
	m_CurrentGoal = SelectFirstVallidPriorityGoal();
	if (m_CurrentGoal)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT(" goal selected : %s"), *m_CurrentGoal->GetGoalName()));
	else
		return;

	//Find the lowest scoring Action that satisfies the goal's desired state
	AGOAPAction* startAction = FindStartAction();
	if (startAction)
	{
		m_CurrentPlan.Add(startAction);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT(" start action selected : %s"), *startAction->GetActionName()));
	}
		
	//Looks recursively for all the actions needed to achieve the current goal
	if (startAction)
		FindAllNeccesaryGOAPActions(startAction);

}

GOAPGoalBase* AGOAPBehaviour::SelectFirstVallidPriorityGoal()
{
	for (const auto& goal : m_AllGOAPGoals)
	{
		if (goal->IsVallid(m_BlackboardRef))
		{
			goal->StartTimer(true);
			return goal;
		}
	}
	return nullptr;
}

void AGOAPBehaviour::UpdateCurrentWorldState()
{
	
}

bool AGOAPBehaviour::CurrentGoalInvallid()
{
	return (m_CurrentGoal && !m_CurrentGoal->IsVallid(m_BlackboardRef));
	
}

AGOAPAction* AGOAPBehaviour::FindStartAction()
{
	//compare currentWorldState with the desiredworldState off the goal
	AWorldStateActor* desiredState = m_CurrentGoal->GetDesiredState();
	if (!desiredState)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT(" start action got NO desiredState ")));

	
	//find the lowest scoring action based from the compared DesiredworldState
	AGOAPAction* possibleAction = nullptr;
	float lowestScore = 100.0f;
	for (const auto& action : m_AllGOAPActions)
	{
		float newScore = action->GetActionScore(CurrentWorldState);
		action->UpdateCost();
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT(" actionscore : %s->score : %f"), *action->GetActionName(), newScore));

		if (action->DoesActionSatisfyGoal(desiredState) && newScore < lowestScore)
		{
			possibleAction = action;
			lowestScore = newScore;
		}
	}
	return possibleAction;
}

void AGOAPBehaviour::FindAllNeccesaryGOAPActions(GOAPActionBase* startAction)
{
	//compare currentWorldState with the desiredworldState off the goal
	AWorldStateActor* currentDesiredWorldState = startAction->GetDesiredState();
	if (!currentDesiredWorldState)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT(" No vallid desird worldstate on action")));
		return;
	}

	ComparedWorldState->ResetWorldState();
	currentDesiredWorldState->CompareWithCurrentState(CurrentWorldState, ComparedWorldState);

	int numOffStatesToSatisfy = ComparedWorldState->GetNumOffUnsatisfiedStates();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT(" states to satisfy: %i"), numOffStatesToSatisfy));


	//return out off recursion if no more actions to find
	if (numOffStatesToSatisfy == 0)
		return;

	//every action can have multiple states to satisfy, first it will create a plan for the first one 
	//the last plan is the one that will be executed first 
	for (int index{ 0 }; index < ComparedWorldState->GetNumOffAllStates(); index++)
	{
		//Redo the worldState since it might have been changed by recursion
		ComparedWorldState->ResetWorldState();
		currentDesiredWorldState->CompareWithCurrentState(CurrentWorldState, ComparedWorldState);

		//look at next one if current state in worldstate is not active
		if (!ComparedWorldState->IsWorldStateActiveAtIndex(index))
			continue;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT(" worldState of goal/action selected : %i"), index));

		//loop over all actions to find the lowest scoring action that satisfies current desired state
		float score = 1000.0f;
		AGOAPAction* bestAction = nullptr;
		for (const auto& action: m_AllGOAPActions)
		{
			
			if (action->DoesActionSatisfyActionState(ComparedWorldState, index))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT(" action satisfy state: %s"), *action->GetActionName()));

				float newScore = action->GetActionScore(CurrentWorldState);
				action->UpdateCost();
				if (newScore < score)
				{
					score = newScore;
					bestAction = action;
				}
			}
		}

		//recursively look for more actions to add if current bestAction has more desiredState.
		if (bestAction)
		{
			m_CurrentPlan.Add(bestAction);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT(" add to plan : %s"), *bestAction->GetActionName()));
			FindAllNeccesaryGOAPActions(bestAction);
		}

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

