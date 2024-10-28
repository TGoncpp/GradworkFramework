#include "SoulsCharacter.h"


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

		nextAction->Execute();
	}

	//Remove actions from queue who stayed to long
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

#pragma region inputhandleling
void ASoulsCharacter::QuickAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(Cast<ABattleActionBase>(m_Actions[EActions::Quick]));

	PrintQueue();
}

void ASoulsCharacter::HardAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(Cast<ABattleActionBase>(m_Actions[EActions::Hard]));
	PrintQueue();
}

void ASoulsCharacter::ThrowAttack(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(Cast<ABattleActionBase>(m_Actions[EActions::Throw]));
	PrintQueue();
}

void ASoulsCharacter::Block(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(Cast<ABattleActionBase>(m_Actions[EActions::Block]));
	PrintQueue();
}

void ASoulsCharacter::Heal(const FInputActionValue& Value)
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
		m_ActionQueue.Add(Cast<ABattleActionBase>(m_Actions[EActions::Heal]));
	PrintQueue();
}

void ASoulsCharacter::AddAction(ABattleActionBase* newAction)
{
	m_Actions.Add(newAction->m_ActionType, newAction);
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
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "new ation");
	for (const auto& action : m_ActionQueue)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,action->GetActionName());
	}
}
