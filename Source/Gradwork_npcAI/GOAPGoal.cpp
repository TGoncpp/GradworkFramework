#include "GOAPGoal.h"
#include "WorldStateActor.h"


// Sets default values
AGOAPGoal::AGOAPGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGOAPGoal::BeginPlay()
{
	Super::BeginPlay();
	m_DesiredState = DesiredState.Get();
	M_NameOfGoal = GoalName;
}

// Called every frame
void AGOAPGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTimer(DeltaTime);
	UpdateTimeOutTimer(DeltaTime);

}

bool AGOAPGoal::IsVallid(BlackBoard* blackboard)const 
{
	return CheckValidationThroughBlackboard(blackboard) && m_IsVallid;
}

void AGOAPGoal::StartTimer(bool start)
{
	IsTimed = start;
	if (!start)
		m_CurrentStoredTime = 0.0f;
}

void AGOAPGoal::SetDesiredWorldState(AWorldStateActor* desiredWorldState)
{
	m_DesiredState = desiredWorldState;
}

bool AGOAPGoal::CheckValidationThroughBlackboard(BlackBoard* blackboard)const
{
	bool isVallid = true;
	for (int index{}; index < ValidBlackboardKey.Num(); index++)
	{
		switch (CompareMethod[index])
		{
		case ECompareMethode::Higher:
			isVallid = blackboard->GetKeyValue(ValidBlackboardKey[index]) > ValidBlackboardValue[index];
			break;
		case ECompareMethode::Equal:
			isVallid = blackboard->GetKeyValue(ValidBlackboardKey[index]) == ValidBlackboardValue[index];
			break;
		case ECompareMethode::Lower:
			isVallid = blackboard->GetKeyValue(ValidBlackboardKey[index]) < ValidBlackboardValue[index];
			break;
		}
		if (AllMethodsMustBeTrue && !isVallid)
			return false;
		else if (!AllMethodsMustBeTrue && isVallid)
			return true;
	}
	return isVallid;

}

void AGOAPGoal::UpdateTimer(float deltaTime)
{
	if (IsTimed)
	{
		m_CurrentStoredTime += deltaTime;
		if (m_CurrentStoredTime >= MaxGoalRunTime)
		{
			m_CurrentStoredTime = 0.0f;
			m_IsVallid = false;
			IsTimed = false;
		}
	}
}

void AGOAPGoal::UpdateTimeOutTimer(float deltaTime)
{
	if (!m_IsVallid)
	{
		m_CurrentStoredTime += deltaTime;
		if (m_CurrentStoredTime >= MaxGoalTimeOutTime)
		{
			m_CurrentStoredTime = 0.0f;
			m_IsVallid = true;
		}
	}
}

void AGOAPGoal::SetValid(bool newValue)
{
	m_IsVallid = newValue;
}

