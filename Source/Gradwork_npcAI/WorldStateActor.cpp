#include "WorldStateActor.h"
#include "BlackBoard.h"
#include "SoulsController.h"
#include "StaminaComponent.h"
#include "HealthComponent.h"

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

void AWorldStateActor::UpdateWorldState(AActor* playerRef, AActor* npcRef)
{
	ASoulsCharacter* player = Cast<ASoulsCharacter>(playerRef);
	ASoulsCharacter* npc = Cast<ASoulsCharacter>(npcRef);

	//Update distance state
	float distance = player->GetDistanceTo(npc);
	if (distance < m_DistanceOfReach)
		m_DistanceToOpponentState = EDistance::Close;
	else if (distance > m_DistanceOfReach && distance < m_DistanceOfHeal)
		m_DistanceToOpponentState = EDistance::OutOfRange;
	else
		m_DistanceToOpponentState = EDistance::HealDistance;

	//Update ActionState
	m_ActionState = npc->GetCurrentAction()->GetActionType();

	//Update enemy ActionState
	m_OpponentActionState = player->GetCurrentAction()->GetActionType();

	//Update condition
	float stamina = npc->GetStaminaComponentRef()->GetStaminaPercentage();
	float health = npc->GetHealthComponentRef()->GetHealthPercentage();
	if (stamina < m_MinValue && health < m_MinValue)
		m_ConditionState = ECondition::Low;
	else if (stamina < m_MinValue )
		m_ConditionState = ECondition::LowSP;
	else if (health < m_MinValue )
		m_ConditionState = ECondition::LowHP;
	else if (stamina > m_HighValue && health > m_HighValue)
		m_ConditionState = ECondition::Perfect;
	else if (stamina > m_HighValue )
		m_ConditionState = ECondition::HighSP;
	else if (health > m_HighValue)
		m_ConditionState = ECondition::HighHP;

	//Update opponent condition
	stamina = player->GetStaminaComponentRef()->GetStaminaPercentage();
	health = player->GetHealthComponentRef()->GetHealthPercentage();
	if (stamina < m_MinValue && health < m_MinValue)
		m_OpponentConditionState = ECondition::Low;
	else if (stamina < m_MinValue )
		m_OpponentConditionState = ECondition::LowSP;
	else if (health < m_MinValue )
		m_OpponentConditionState = ECondition::LowHP;
	else if (stamina > m_HighValue && health > m_HighValue)
		m_OpponentConditionState = ECondition::Perfect;
	else if (stamina > m_HighValue )
		m_OpponentConditionState = ECondition::HighSP;
	else if (health > m_HighValue)
		m_OpponentConditionState = ECondition::HighHP;
	


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
