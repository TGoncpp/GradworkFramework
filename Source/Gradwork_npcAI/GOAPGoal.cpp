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

}

bool AGOAPGoal::IsVallid(BlackBoard* blackboard)const 
{
	return CheckValidationThroughBlackboard(blackboard);
}

void AGOAPGoal::SetDesiredWorldState(AWorldStateActor* desiredWorldState)
{
	m_DesiredState = desiredWorldState;
}

bool AGOAPGoal::CheckValidationThroughBlackboard(BlackBoard* blackboard)const
{
	switch (CompareMethod)
	{
	case ECompareMethode::Higher:
		return blackboard->GetKeyValue(ValidBlackboardKey) > ValidBlackboardValue;
	case ECompareMethode::Equal:
		return blackboard->GetKeyValue(ValidBlackboardKey) == ValidBlackboardValue;
	case ECompareMethode::Lower:
		return blackboard->GetKeyValue(ValidBlackboardKey) < ValidBlackboardValue;
	}
	return false;
	
}

