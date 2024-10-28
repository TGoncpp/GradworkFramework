#include "SoulsCharacter.h"
#include "BattleActionBase.h"


void ASoulsCharacter::Tick(float DeltaTime)
{
	//Do nothing if no actions enqueued
	if (m_ActionQueue.Num() <= 0)
		return;

	//if not doing an action, start the first off the queue
	if (m_IsIdle)
	{
		m_IsIdle = false;
		ABattleActionBase* nextAction = m_ActionQueue[0];
		m_ActionQueue.PopFront();
		GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsCharacter::ReturnToIdle,nextAction->GetExecutionTime(), false);
		nextAction->EnQueue(MAX_IN_QUEUE_TIME);
	}

	//Remove actions in queue who stayed to long
	const float elapsedTime = GetWorld()->GetDeltaSeconds();
	for (auto action : m_ActionQueue)
	{
		if (action->ToLongInQueue(elapsedTime))
		{
			m_ActionQueue.Remove(action);
		}
	}

}

void ASoulsCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_ActionQueue.Reserve(MAX_QUEUESIZE);
}


//implementations
//--------------------------------------------------------------

void ASoulsCharacter::QuickAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Quick]);
}

void ASoulsCharacter::HardAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Hard]);

}

void ASoulsCharacter::ThrowAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Throw]);

}

void ASoulsCharacter::Block(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Block]);

}

void ASoulsCharacter::Heal(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(m_Actions[EActions::Heal]);

}



void ASoulsCharacter::ExecuteAttacks()
{
	
}

void ASoulsCharacter::ReturnToIdle()
{
	m_IsIdle = true;
}
