#include "SoulsCharacter.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "KnockbackComponent.h"


ASoulsCharacter::ASoulsCharacter()
{
	//Add healthComponent
	m_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("healthComp"));
	AddOwnedComponent(m_HealthComponent);

	//Add StaminaComponent
	m_StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("staminaComp"));
	AddOwnedComponent(m_StaminaComponent);

	//Add knockbackComponent
	m_KnockbackComponent = CreateDefaultSubobject<UKnockBackComponent>(TEXT("KnockbackComp"));
	AddOwnedComponent(m_KnockbackComponent);
}

void ASoulsCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_ActionQueue.Reserve(MAX_QUEUESIZE);
	Tags.Add("Body");

	//add event for dead from healthcomponent
	m_HealthComponent->OnDead.AddDynamic(this, &ASoulsCharacter::Ragdoll);
	//add event for revive from healthcomponent
	m_HealthComponent->OnRevive.AddDynamic(this, &ASoulsCharacter::RiseAgain);
	//add event for knockback from knockbackcomponent
	m_KnockbackComponent->OnGetHit.AddDynamic(this, &ASoulsCharacter::ResetQueue);
}

void ASoulsCharacter::Tick(float DeltaTime)
{
	//Do nothing if no actions enqueued
	if (m_ActionQueue.Num() <= 0 )
		return;
	//When stunned but block is still active
	if (m_KnockbackComponent->IsStunned())
	{
		StopBlock();
		return;
	}

	//if not doing an action, start the first off the queue
	if (m_IsIdle)
	{
		m_IsIdle = false;

		m_ActivatedAction = m_ActionQueue.First();
		m_ActionQueue.PopFront();
		
		//if action is block -> continue until it is released. else stop after set amount off time
		if (m_ActivatedAction->GetActionType() != EActions::Block)
			GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsCharacter::ReturnToIdle, m_ActivatedAction->GetExecutionTime(), false);

		m_ActivatedAction->EnQueue(MAX_IN_QUEUE_TIME);

		if (m_ActivatedAction->HasSufficentStamina())
			m_ActivatedAction->Execute();
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

void ASoulsCharacter::StopBlock()
{
	if (!m_ActivatedAction || m_ActivatedAction->GetActionType() != EActions::Block)
		return;

	//set to true to activate the queue again
	m_IsIdle = true;
	//remove all other actions from queue, else it get stuck on second block.
	int size = m_ActionQueue.Num();
	m_ActionQueue.PopFront(size);
	//Deactivate the blueprint, this is only with blocking because other actions will be cancelled at a timer
	m_ActivatedAction->DeActivate();
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

void ASoulsCharacter::ResetQueue()
{
	int size = m_ActionQueue.Num();
	if (size > 0)
		m_ActionQueue.Pop(size);
	
	if (m_ActivatedAction)
		m_ActivatedAction->ResetAction();
}
