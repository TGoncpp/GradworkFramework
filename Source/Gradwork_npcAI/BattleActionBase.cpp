#include "BattleActionBase.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "KnockbackComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIBehaviourBase.h" // for enum values


ABattleActionBase::ABattleActionBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABattleActionBase::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Weapon");

	m_TriggerCapsule = FindComponentByClass< UCapsuleComponent>();
	checkf(m_TriggerCapsule, TEXT("No capsuleComponent found in battle action called: %s"), *ActionName);
	m_TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABattleActionBase::OnOverlapBegin);
	
}
 
void ABattleActionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//update will happen in blueprint
}



void ABattleActionBase::EnQueue(float timePermitedInQueue)
{
	m_InQueueTimeLeft = timePermitedInQueue;
}

bool ABattleActionBase::ToLongInQueue(float deltaTime)
{
	m_InQueueTimeLeft -= deltaTime;

	return m_InQueueTimeLeft <= 0.f;
}

bool ABattleActionBase::HasSufficentStamina() const
{
	checkf(m_ParentActor, TEXT("is not parented action name : %s"), *ActionName);

	UStaminaComponent* staminaComp = m_ParentActor->FindComponentByClass<UStaminaComponent>();
	return staminaComp->SuccesfullExecution(Cost);
}

bool ABattleActionBase::IsBlocking() const
{
	return m_ActionType == EAction::Block;
}

bool ABattleActionBase::IsHealing() const
{
	return m_ActionType == EAction::Heal;
}

bool ABattleActionBase::IsThrowing() const
{
	return m_ActionType == EAction::Throw;
}

bool ABattleActionBase::IsAttacking() const
{
	return m_ActionType == EAction::QuickAttack || m_ActionType == EAction::HardAttack || m_ActionType == EAction::Throw;
}

bool ABattleActionBase::IsQuickAttacking() const
{
	return m_ActionType == EAction::QuickAttack;
}

bool ABattleActionBase::IsStraightForwardAttacking() const
{
	return m_ActionType == EAction::HardAttack || m_ActionType == EAction::Throw;
}


UCharacterMovementComponent* ABattleActionBase::GetParentMovementComp() const
{
	return m_ParentMovementComp;;
}

void ABattleActionBase::SimulateHitActor(AActor* hitActor)
{
	FHitResult hitResult;
	OnOverlapBegin(nullptr, hitActor, nullptr, 0, false, hitResult);
}

void ABattleActionBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->Tags.Contains("Body") && OtherActor != m_ParentActor)
	{
		//STUNNED
		UKnockBackComponent* enemyKnockbackComp = OtherActor->FindComponentByClass<UKnockBackComponent>();
		if (enemyKnockbackComp && enemyKnockbackComp->IsStunned())
			return;
			

		//BLOCK
		//get refrence off current action off OtherActor
		ABattleActionBase* blockAction = nullptr;
		TArray<AActor*> AttachedActors;
		OtherActor->GetAttachedActors(AttachedActors);
		for (AActor* Actor : AttachedActors)
		{
			if (Actor->Tags.Contains("Block"))
			{
				blockAction = Cast<ABattleActionBase>(Actor);
			}
		}

		//Check if blocking
		if (blockAction && blockAction->BlockIsActive)
		{
			//adjust stamina if block
			UStaminaComponent* enemyStaminaComp = OtherActor->FindComponentByClass<UStaminaComponent>();
			bool isHardAttack = m_ActionType == EAction::HardAttack;
			if (enemyStaminaComp && enemyStaminaComp->SuccesfullExecution(Damage, isHardAttack))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Blocked");
				DeActivate();
				return;
			}
			//if block failes, stop block and clear stamina
			//when stunned, block will be stopped in soulsCharacter Tick
			enemyStaminaComp->ClearStamina();
		}


		//NO BLOCK
		//send message to enemy health component
		UHealthComponent* enemyHealthComp = OtherActor->FindComponentByClass<UHealthComponent>();
		if (enemyHealthComp)
		{
			enemyHealthComp->RecieveDamage(Damage);
		}

		//send message to enemy knockback component
		if (enemyKnockbackComp)
		{
			FVector direction = OtherActor->GetActorLocation() - GetActorLocation();
			direction.Normalize();
			direction.Z = 0.1f;
			enemyKnockbackComp->RecieveDamage(direction, KnockTime);
		}

	}
}


void ABattleActionBase::AddParent(AActor* parent)
{
	m_ParentActor = parent;
}

void ABattleActionBase::AddParentMovementComp(UCharacterMovementComponent* parentMoveComp)
{
	m_ParentMovementComp = parentMoveComp;
}

