#include "WorldStateActor.h"

// Sets default values
AWorldStateActor::AWorldStateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldStateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldStateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


int AWorldStateActor::GetNumOffUnsatisfiedStates() const
{
	int numOffUnsatisfiedStates = 0;
	for (const bool& worldState : m_IsActiveWorldStates)
	{
		if (worldState)
			numOffUnsatisfiedStates++;
	}

	return numOffUnsatisfiedStates;
}

int AWorldStateActor::GetNumOffAllStates() const
{
	return m_IsActiveWorldStates.Num();
}

TArray<int> AWorldStateActor::GetIndexOffAllActiveStates() const
{
	TArray<int> indexes;
	for (int index{}; index < m_IsActiveWorldStates.Num(); index++)
	{
		if (m_IsActiveWorldStates[index])
			indexes.Add(index);
	}
	return indexes;
}

void AWorldStateActor::UpdateWorldState(AWorldStateActor* WorldState)
{

}

EGoal AWorldStateActor::GetGoalState() const
{
	return m_GoalState;
}

EAction AWorldStateActor::GetActionState() const
{
	return m_ActionState;
}

EAction AWorldStateActor::GetOpponentActionState() const
{
	return m_OpponentActionState;
}

ECondition AWorldStateActor::GetConditionState() const
{
	return m_ConditionState;
}

ECondition AWorldStateActor::GetOpponentConditionState() const
{
	return m_OpponentConditionState;
}

EDistance AWorldStateActor::GetDistanceState() const
{
	return m_DistanceToOpponentState;
}

bool AWorldStateActor::IsWorldStateEqualOnIndex(AWorldStateActor* otherWorldState, int index) const
{
	switch (index)
	{
	case 0:
		return m_GoalState == otherWorldState->GetGoalState();
	case 1:
		return m_ActionState == otherWorldState->GetActionState();
	case 2:
		return m_OpponentActionState == otherWorldState->GetOpponentActionState();
	case 3:
		return m_ConditionState == otherWorldState->GetConditionState();
	case 4:
		return m_OpponentConditionState == otherWorldState->GetOpponentConditionState();
	case 5:
		return m_DistanceToOpponentState == otherWorldState->GetDistanceState();
	}
	return false;
}

bool AWorldStateActor::IsWorldStateActiveAtIndex(int index) const
{
	return m_IsActiveWorldStates[index];
}
