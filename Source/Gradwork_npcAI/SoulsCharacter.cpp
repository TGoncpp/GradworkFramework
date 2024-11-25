#include "SoulsCharacter.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "KnockbackComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIBehaviourBase.h"// for enum values


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
	//add event for revive from healthcomponent
	if (m_HealthComponent)
	{
		m_HealthComponent->OnDead.AddDynamic(this, &ASoulsCharacter::Ragdoll);
		m_HealthComponent->OnRevive.AddDynamic(this, &ASoulsCharacter::RiseAgain);
	}
	//add event for knockback from knockbackcomponent
	if (m_KnockbackComponent)
		m_KnockbackComponent->OnGetHit.AddDynamic(this, &ASoulsCharacter::ResetQueue);
}

void ASoulsCharacter::Tick(float DeltaTime)
{
	if (m_IsLockOn)
		LookAtTarget();
	
	//Do nothing if no actions enqueued
	if (m_ActionQueue.Num() <= 0 )
		return;
	//When stunned but block is still active
	if (m_KnockbackComponent && m_KnockbackComponent->IsStunned())
	{
		StopBlock();
		return;
	}
	
	//if not doing an action, start the first off the queue
	if (m_IsIdle)
	{
		m_ActivatedAction = m_ActionQueue.First();
		m_ActionQueue.PopFront();
		
		if (m_ActivatedAction->HasSufficentStamina())
		{
			m_IsIdle = false;
			m_ActivatedAction->Execute();

			//if action is block -> continue until it is released. else stop after set amount off time
			if (m_ActivatedAction->GetActionType() != EAction::Block)
				GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsCharacter::ReturnToIdle, m_ActivatedAction->GetExecutionTime(), false);
		
			m_ActivatedAction->EnQueue(m_MaxInQueueTime);
		}
		else
			m_ActivatedAction = nullptr;
	}
	
	RemoveActionsThatAreToLongInQueue();

}

UHealthComponent* ASoulsCharacter::GetHealthComponentRef() const
{
	return m_HealthComponent;
}

UStaminaComponent* ASoulsCharacter::GetStaminaComponentRef() const
{
	return m_StaminaComponent;
}

UKnockBackComponent* ASoulsCharacter::GetKnockbackComponentRef() const
{
	return m_KnockbackComponent;
}

ABattleActionBase* ASoulsCharacter::GetCurrentAction() const
{
	return m_ActivatedAction;
}

void ASoulsCharacter::RemoveActionsThatAreToLongInQueue()
{
	//go over all and keep number off action that are overtime
	const float elapsedTime = GetWorld()->GetDeltaSeconds();
	int numOfOvertime = 0;
	for (auto action : m_ActionQueue)
	{
		// dont add block so the time after release and block stop remains consistent
		if (action->ToLongInQueue(elapsedTime) && action->GetActionType() != EAction::Block) 
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
	{
		auto newAction = FindActionOffType(EAction::QuickAttack);
		checkf(newAction, TEXT("quick action is invallid"));
		m_ActionQueue.Add(newAction);
	}
	PrintQueue();
}

void ASoulsCharacter::HardAttack()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
	{
		auto newAction = FindActionOffType(EAction::HardAttack);
		checkf(newAction, TEXT("Hard action is invallid"));
		m_ActionQueue.Add(newAction);
	}
	PrintQueue();
}

void ASoulsCharacter::ThrowAttack()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
	{
		auto newAction = FindActionOffType(EAction::Throw);
		checkf(newAction, TEXT("throw action is invallid"));
		m_ActionQueue.Add(newAction);
	}
	PrintQueue();
}

void ASoulsCharacter::Block()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
	{
		auto newAction = FindActionOffType(EAction::Block);
		checkf(newAction, TEXT("block action is invallid"));
		m_ActionQueue.Add(newAction);
	}
	PrintQueue();
}

void ASoulsCharacter::StopBlock()
{
	if (!m_ActivatedAction || m_ActivatedAction->GetActionType() != EAction::Block)
		return;
	
	//set to true to activate the queue again
	m_IsIdle = true;

	//remove all other actions from queue, else it get stuck on second block.
	int size = m_ActionQueue.Num();
	m_ActionQueue.PopFront(size);

	//Deactivate the blueprint, this is only with blocking because other actions will be cancelled at a timer
	m_ActivatedAction->DeActivate();
	m_ActivatedAction = nullptr;

}

void ASoulsCharacter::Heal()
{
	if (m_ActionQueue.Num() < MAX_QUEUESIZE)
	{
		auto newAction = FindActionOffType(EAction::Heal);
		checkf(newAction, TEXT("heal action is invallid"));
		m_ActionQueue.Add(newAction);
	}	
	PrintQueue();
}

void ASoulsCharacter::LockOn()
{
	if (!m_Target)
	{
		m_IsLockOn = false;
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Lock on failed")));

		return;
	}

	m_IsLockOn = !m_IsLockOn;

}

void ASoulsCharacter::FoundTarget(ASoulsCharacter* target)
{
	m_Target = target;
}

void ASoulsCharacter::AddAction(ABattleActionBase* newAction)
{
	m_Actions.Add(newAction);
	newAction->AddParent(this);
	newAction->AddParentMovementComp(GetCharacterMovement());

}

void ASoulsCharacter::SetActionEnqueueTime(float newTime)
{
	m_MaxInQueueTime = newTime;
}

#pragma endregion inputhandeling


void ASoulsCharacter::ExecuteAttacks()
{
	
}

void ASoulsCharacter::ReturnToIdle()
{
	m_IsIdle = true;
	m_ActivatedAction = nullptr;
}

void ASoulsCharacter::PrintQueue()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::FromInt( m_ActionQueue.Num()));
	//for (const auto& action : m_ActionQueue)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,action->GetActionName());
	//}
}

ABattleActionBase* ASoulsCharacter::FindActionOffType(EAction actionType)
{
	for (const auto& action : m_Actions)
	{
		if (action->GetActionType() == actionType)
			return action;
	}
	return nullptr;
}

void ASoulsCharacter::ResetQueue()
{
	int size = m_ActionQueue.Num();
	if (size > 0)
		m_ActionQueue.Pop(size);
	
	if (m_ActivatedAction)
	{
		m_ActivatedAction->DeActivate();
		m_ActivatedAction = nullptr;
	}
}

void ASoulsCharacter::LookAtTarget()
{
	FVector ActorLocation = GetActorLocation();
	FVector TargetLocation;
	if (m_Target)
		TargetLocation = m_Target->GetActorLocation();

	// Calculate the rotation needed to look at the target
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

	// Set the actor's rotation to the calculated rotation
	
	SetActorRotation(LookAtRotation, ETeleportType::None);
}
