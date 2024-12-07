#include "GOAPAction.h"
#include "WorldState.h"


AGOAPAction::AGOAPAction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGOAPAction::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGOAPAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGOAPAction::IsFinished()const 
{
	return IsActionFinished;
}

void AGOAPAction::UpdateAction()
{
	UpdateActionImplementation();
}

EAction AGOAPAction::GetActionInput()const 
{
	return ActionInput;
}

