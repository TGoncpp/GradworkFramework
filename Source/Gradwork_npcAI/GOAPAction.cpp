#include "GOAPAction.h"


AGOAPAction::AGOAPAction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGOAPAction::BeginPlay()
{
	Super::BeginPlay();
	m_DesiredState = DesiredState.Get();
	m_SatisfiesState = SatisfiesState.Get();
	m_ComparedWorldState = ComparedState.Get();
	m_Cost = Cost;
}

void AGOAPAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGOAPAction::IsFinished()
{
	if (IsActionFinished)
	{
		IsActionFinished = false;
		return true;
	}
	return false;
}

void AGOAPAction::UpdateAction(BlackBoard* blackboard)
{
	//set to isFinished in blueprint if action allows it
	UpdateActionImplementation();

	//check through blackboard if action is finished, the keys to check are set in the blueprint off the action
	if (UpdateBlackboardKey.Num() == 0)
		return;

	//only if all comparisons are correct set isActionFinished to true
	for (int index{}; index < UpdateBlackboardKey.Num(); index++)
	{
		if (!CompareBlackboardValues(blackboard, UpdateBlackboardKey[index], UpdateBlackboardValue[index], UpdateCompareMethode[index]))
			return;
	}
	IsActionFinished = true;
}

EAction AGOAPAction::GetActionInput()const 
{
	return ActionInput;
}

FString AGOAPAction::GetActionName() const
{
	if (ActionName.IsEmpty())
		return "NoName";

	return ActionName;
}

bool  AGOAPAction::CompareBlackboardValues(BlackBoard* blackboard, const FString& key, float comparedValue, ECompareMethode compareMethode)
{
	switch (compareMethode)
	{
	case ECompareMethode::Higher:
		if (blackboard->GetKeyValue(key) <= comparedValue)
			return false;
		break;
	case ECompareMethode::Equal:
		if (blackboard->GetKeyValue(key) != comparedValue)
			return false;
		break;
	case ECompareMethode::Lower:
		if (blackboard->GetKeyValue(key) >= comparedValue)
			return false;
		break;
	}
	return true;
}

