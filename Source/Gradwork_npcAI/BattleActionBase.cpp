#include "BattleActionBase.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "KnockbackComponent.h"
#include "Components/CapsuleComponent.h"

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
	M_InQueueTimeLeft = timePermitedInQueue;
}

bool ABattleActionBase::ToLongInQueue(float deltaTime)
{
	M_InQueueTimeLeft -= deltaTime;

	return M_InQueueTimeLeft <= 0.f;
}

bool ABattleActionBase::HasSufficentStamina() const
{
	checkf(m_ParentActor, TEXT("is not parented action name : %s"), *ActionName);

	UStaminaComponent* staminaComp = m_ParentActor->FindComponentByClass<UStaminaComponent>();
	return staminaComp->SuccesfullExecution(Cost);
}


void ABattleActionBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->Tags.Contains("Body"))
	{
		//BLOCK
		//get refrence off current action off OtherActor
		ABattleActionBase* blockAction = nullptr;
		TArray<AActor*> AttachedActors;
		OtherActor->GetAttachedActors(AttachedActors);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Found Action num : %i"), AttachedActors.Num()));
		for (AActor* Actor : AttachedActors)
		{
			if (Actor->Tags.Contains("Block"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Found blockAction");
				blockAction = Cast<ABattleActionBase>(Actor);
			}
		}

		//Check if blocking
		if (blockAction && blockAction->BlockIsActive)
		{
			//adjust stamina if block
			UStaminaComponent* enemyStaminaComp = OtherActor->FindComponentByClass<UStaminaComponent>();
			if (enemyStaminaComp && enemyStaminaComp->SuccesfullExecution(Damage))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Blocked");
				//TODO: send message to attack to deactivate
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
		UKnockBackComponent* enemyKnockbackComp = OtherActor->FindComponentByClass<UKnockBackComponent>();
		if (enemyKnockbackComp)
		{
			FVector direction = OtherActor->GetActorLocation() - GetActorLocation();
			direction.Normalize();
			direction.Z = 0.1f;
			enemyKnockbackComp->RecieveDamage(direction, KnockPower);
		}

	}
}


void ABattleActionBase::AddParent(AActor* parent)
{
	m_ParentActor = parent;
}

