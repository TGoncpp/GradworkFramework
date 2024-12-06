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

void AGOAPBehaviour::CreateNewPlan()
{
	m_CurrentGoal = SelectFirstVallidPriorityGoal();

	WorldState* desiredState = m_CurrentGoal->GetDisiredState();



}

void AGOAPBehaviour::FindAllNeccesaryGOAPActions()
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

