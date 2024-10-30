#include "BattleActionBase.h"
//#include "SoulsCharacter.h"
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "Components/CapsuleComponent.h"

ABattleActionBase::ABattleActionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
		//ASoulsCharacter* enemy = Cast<ASoulsCharacter>(OtherActor);
		UHealthComponent* enemyHealthComp = OtherActor->FindComponentByClass<UHealthComponent>();
		if (enemyHealthComp)
		{
			enemyHealthComp->RecieveDamage(Damage);
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "collision");

	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "fake collision");
}


void ABattleActionBase::AddParent(AActor* parent)
{
	m_ParentActor = parent;
}

