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
	
}

// Called every frame
void AGOAPGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGOAPGoal::IsVallid(BlackBoard* blackboard) 
{
	return CheckValidationThroughBlackboard(blackboard);
	 ;
}

void AGOAPGoal::SetDesiredWorldState(AWorldStateActor* desiredWorldState)
{
	m_DiseredState = desiredWorldState;
}

bool AGOAPGoal::CheckValidationThroughBlackboard(BlackBoard* blackboard)
{
	return blackboard->GetKeyValue(ValidBlackboardKey) == ValidBlackboardValue;
}

