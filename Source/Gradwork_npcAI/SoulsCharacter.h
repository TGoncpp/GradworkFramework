// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gradwork_npcAICharacter.h"
#include "Containers/RingBuffer.h"
#include "TimerManager.h"
#include "Containers/Map.h"
#include "BattleActionBase.h"


#include "SoulsCharacter.generated.h"

//class ABattleActionBase;
enum class EActions;
class UHealthComponent;
class UStaminaComponent;


UCLASS(Blueprintable)
class GRADWORK_NPCAI_API ASoulsCharacter : public AGradwork_npcAICharacter
{
	GENERATED_BODY()

public:
	ASoulsCharacter();
	virtual void Tick(float DeltaTime) override;
	void RemoveActionsThatAreToLongInQueue();
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EActions, ABattleActionBase*> m_Actions;

	//Battle Actions
	/** fast attack input */
	virtual void QuickAttack()override;

	/** fast attack input */
	virtual void HardAttack()override;

	/** fast attack input */
	virtual void ThrowAttack()override;

	/** fast attack input */
	virtual void Block()override;
				
	/** fast attack input */
	virtual void Heal()override;

protected:
	UPROPERTY(VisibleAnywhere)
	UHealthComponent* m_HealthComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaminaComponent* m_StaminaComponent = nullptr;

#pragma region mapsetting

	UFUNCTION(BlueprintCallable)
	void AddAction(ABattleActionBase* newAction);

#pragma endregion mapsetting


private:
	FTimerHandle  m_Timer;

	bool m_IsIdle = true;
	const int MAX_QUEUESIZE = 5;
	const float MAX_IN_QUEUE_TIME = 1.0f;
	TRingBuffer< ABattleActionBase*> m_ActionQueue;

	void ExecuteAttacks();

	void ReturnToIdle();

	//DebugFunctions
	void PrintQueue();
	
};
