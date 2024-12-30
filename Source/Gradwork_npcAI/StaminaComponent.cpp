// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	m_Stamina = MAX_STAMINA;
	
}

void UStaminaComponent::Regenerate(float deltaTime)
{
	if (m_Stamina < MAX_STAMINA)
		m_Stamina += REGENERATION_RATE * deltaTime;
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Regenerate(DeltaTime);
}

bool UStaminaComponent::SuccesfullExecution(float cost, bool intenseAction)
{
	float totalCost = intenseAction ? cost * 1.5f : cost;
	//early return if not enough
	if (m_Stamina < totalCost) return false;

	//reduce stamina lowest at 0
	m_Stamina -= totalCost;
	if (m_Stamina < 0.0f) 
		m_Stamina = 0.0f;

	return true;
}

void UStaminaComponent::ClearStamina()
{
	m_Stamina = 0.0f;
}

void UStaminaComponent::FullStamina()
{
	m_Stamina = MAX_STAMINA;
}

