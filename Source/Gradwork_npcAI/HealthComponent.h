// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReviveEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRADWORK_NPCAI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthPercentage() const { return m_Health/MAX_HEALTH; }
	void RecieveDamage(float damage);
	UFUNCTION(BlueprintCallable, Category = "Heal")
	void Recover();

	void Die();
	void Revive();
	void FullHealth();

	UPROPERTY()
	FDeadEvent OnDead;
	
	UPROPERTY()
	FReviveEvent OnRevive;
		
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	float m_Health = 0.0f;
	const float MAX_HEALTH = 100.0f;
	float m_ReviveTime = 2.0f;

	FTimerHandle  m_Timer;

};
