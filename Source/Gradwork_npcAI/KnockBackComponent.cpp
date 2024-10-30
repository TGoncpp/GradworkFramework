#include "KnockBackComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UKnockBackComponent::UKnockBackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKnockBackComponent::BeginPlay()
{
	Super::BeginPlay();

	m_OwnerMovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	checkf(m_OwnerMovementComponent, TEXT("no vallid or missing charactermovementcomponent found for knockbackComponent"));
	
}


// Called every frame
void UKnockBackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_WasHit)
		return;

	//move player in knowkback direction
	GetOwner()->AddActorLocalOffset(m_NormalisedKnockDirection * m_FallSpeed * DeltaTime);
	m_CurrentKnockTime -= DeltaTime;

	//update stunTime
	if (m_CurrentKnockTime <= 0.0f)
	{
		m_CurrentKnockTime = 0.0f;
		m_WasHit = false;

		if (m_OwnerMovementComponent)
		{
			m_OwnerMovementComponent->SetMovementMode(MOVE_Walking);
		}
	}


}

void UKnockBackComponent::RecieveDamage(const FVector& direction, float knocktime)
{
	m_NormalisedKnockDirection = direction;
	m_CurrentKnockTime = knocktime;
	m_WasHit = true;

	if (m_OwnerMovementComponent)
	{
		m_OwnerMovementComponent->DisableMovement();
	}

	//TODO send message to player 
	//reset actions                -
	//clear actionqueue            X 
	//disable actions              X

	//TODO : check what goes wrong here
	OnGetHit.Broadcast();

}

