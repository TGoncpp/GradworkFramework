#include "SoulsCharacter.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"


ASoulsCharacter::ASoulsCharacter()
{
	//Add healthComponent
	m_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("healthComp"));
	AddOwnedComponent(m_HealthComponent);

	//Add StaminaComponent
	m_StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("staminaComp"));
	AddOwnedComponent(m_StaminaComponent);
}

void ASoulsCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_ActionQueue.Reserve(MAX_QUEUESIZE);
	Tags.Add("Body");
}

void ASoulsCharacter::Tick(float DeltaTime)
{
	//Do nothing if no actions enqueued
	if (m_ActionQueue.Num() <= 0)
		return;

	//if not doing an action, start the first off the queue
	if (m_IsIdle)
	{
		m_IsIdle = false;

		ABattleActionBase* nextAction = m_ActionQueue.First();
		m_ActionQueue.PopFront();
		GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsCharacter::ReturnToIdle,nextAction->GetExecutionTime(), false);
		nextAction->EnQueue(MAX_IN_QUEUE_TIME);

		if (nextAction->HasSufficentStamina())
			nextAction->Execute();
	}

	//RemoveActionsThatAreToLongInQueue();

}

void ASoulsCharacter::RemoveActionsThatAreToLongInQueue()
{
	//go over all and keep number off action that are overtime
	const float elapsedTime = GetWorld()->GetDeltaSeconds();
	int numOfOvertime = 0;
	for (auto action : m_ActionQueue)
	{
		// dont add block so the time after release and block stop remains consistent
		if (action->ToLongInQueue(elapsedTime) && action->GetActionType() != EActions::Block) 
		{
			++numOfOvertime;
		}
	}

	//remove the amount that was overtime from the front off queue
	m_ActionQueue.PopFront(numOfOvertime);
}


//implementations
//--------------------------------------------------------------

#pragma region inputhandleling
void ASoulsCharacter::QuickAttack()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Quick]);
	PrintQueue();
}

void ASoulsCharacter::HardAttack()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Hard]);
	PrintQueue();
}

void ASoulsCharacter::ThrowAttack()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Throw]);
	PrintQueue();
}

void ASoulsCharacter::Block()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Block]);

	PrintQueue();
}

void ASoulsCharacter::Heal()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Heal]);
	PrintQueue();
}

void ASoulsCharacter::AddAction(ABattleActionBase* newAction)
{
	m_Actions.Add(newAction->m_ActionType, newAction);
	newAction->AddParent(this);
}

#pragma endregion inputhandeling


void ASoulsCharacter::ExecuteAttacks()
{
	
}

void ASoulsCharacter::ReturnToIdle()
{
	m_IsIdle = true;
}

void ASoulsCharacter::PrintQueue()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::FromInt( m_ActionQueue.Num()));
	//for (const auto& action : m_ActionQueue)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,action->GetActionName());
	//}
}
