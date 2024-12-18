#include "WorldStateActor.h"
#include "BlackBoard.h"
#include "SoulsController.h"
#include "StaminaComponent.h"
#include "HealthComponent.h"
#include "AIBehaviourBase.h"

// Sets default values
AWorldStateActor::AWorldStateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_IsActiveWorldStates.SetNum(6, false);
	m_ActionState = EAction::Idle;
	m_OpponentActionState = EAction::Idle;
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
	ABattleActionBase* action =  npc->GetCurrentAction();
	if (action)
		m_ActionState = npc->GetCurrentAction()->GetActionType();
	else
		m_ActionState = EAction::Idle;

	//Update enemy ActionState
	action = player->GetCurrentAction();
	if (action)
		m_OpponentActionState = action->GetActionType();
	else
		m_OpponentActionState = EAction::Idle;


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

void AWorldStateActor::SetGoalState(EGoal newGoal)
{
	m_GoalState = newGoal;
}

EAction AWorldStateActor::GetActionState() const
{
	return m_ActionState;
}

void AWorldStateActor::SetActionState(EAction newAction)
{
	m_ActionState = newAction;
}

EAction AWorldStateActor::GetOpponentActionState() const
{
	return m_OpponentActionState;
}

void AWorldStateActor::SetOpponentActionState(EAction newAction)
{
	m_OpponentActionState = newAction;
}

ECondition AWorldStateActor::GetConditionState() const
{
	return m_ConditionState;
}

void AWorldStateActor::SetConditionState(ECondition newCondition)
{
	m_ConditionState = newCondition;
}

ECondition AWorldStateActor::GetOpponentConditionState() const
{
	return m_OpponentConditionState;
}

void AWorldStateActor::SetOpponentConditionState(ECondition newCondition)
{
	m_OpponentConditionState = newCondition;
}

EDistance AWorldStateActor::GetDistanceState() const
{
	return m_DistanceToOpponentState;
}

void AWorldStateActor::SetDistanceState(EDistance newDistance)
{
	m_DistanceToOpponentState = newDistance;
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
		return m_OpponentConditionState == otherWorldState->GetOpponentConditionState();
	case 4:
		return m_DistanceToOpponentState == otherWorldState->GetDistanceState();
	case 5:
		return m_ConditionState == otherWorldState->GetConditionState();
	}
	return false;
}

void AWorldStateActor::CompareWithCurrentState(AWorldStateActor* currentWorldState, AWorldStateActor* newWorldState) const
{
	for (int index{}; index < m_IsActiveWorldStates.Num(); index++)
	{
		if (m_IsActiveWorldStates[index] && !IsWorldStateEqualOnIndex(currentWorldState, index))
		{
			newWorldState->SetDesiredIndex(index);
			switch (index)
			{
			case 0:
				newWorldState->SetGoalState(m_GoalState);
				break;
			case 1:
				newWorldState->SetActionState(m_ActionState);
				break;
			case 2:
				newWorldState->SetOpponentActionState(m_OpponentActionState);
				break;
			case 3:
				newWorldState->SetOpponentConditionState(m_OpponentConditionState);
				break;
			case 4:
				newWorldState->SetDistanceState(m_DistanceToOpponentState);
				break;
			case 5:
				newWorldState->SetConditionState(m_ConditionState);
				break;
			}
		}
	}

}

bool AWorldStateActor::IsWorldStateActiveAtIndex(int index) const
{
	return m_IsActiveWorldStates[index];
}

void AWorldStateActor::SetDesiredIndex(int index)
{
	m_IsActiveWorldStates[index] = true;
	
}

void AWorldStateActor::ResetWorldState()
{
	for (bool& e : m_IsActiveWorldStates)
	{
		e = false;
	}
}
