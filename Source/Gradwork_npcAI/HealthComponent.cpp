
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_Health = MAX_HEALTH;
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::RecieveDamage(float damage)
{
	m_Health -= damage;

	if (m_Health <= 0)
		Die();
}

void UHealthComponent::Recover()
{
	m_Health += MAX_HEALTH * 0.7f;
	if (m_Health > MAX_HEALTH)
		m_Health = MAX_HEALTH;
}

void UHealthComponent::Die()
{
	OnDead.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &UHealthComponent::Revive, m_ReviveTime, false);
}

void UHealthComponent::Revive()
{
	m_Health = MAX_HEALTH;
	OnRevive.Broadcast();
}

void UHealthComponent::FullHealth()
{
	m_Health = MAX_HEALTH;
}

