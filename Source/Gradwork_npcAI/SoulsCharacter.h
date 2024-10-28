// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gradwork_npcAICharacter.h"
#include "Containers/RingBuffer.h"
#include "TimerManager.h"
#include "Containers/Map.h"


#include "SoulsCharacter.generated.h"

class ABattleActionBase;
enum class EActions;


UCLASS()
class GRADWORK_NPCAI_API ASoulsCharacter : public AGradwork_npcAICharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


protected:
	//Battle Actions
	/** fast attack input */
	virtual void QuickAttack(const FInputActionValue& Value)override;

	/** fast attack input */
	virtual void HardAttack(const FInputActionValue& Value)override;

	/** fast attack input */
	virtual void ThrowAttack(const FInputActionValue& Value)override;

	/** fast attack input */
	virtual void Block(const FInputActionValue& Value)override;
				
	/** fast attack input */
	virtual void Heal(const FInputActionValue& Value)override;


private:
	FTimerHandle  m_Timer;

	bool m_IsIdle = true;
	const int MAX_QUEUESIZE = 5;
	const float MAX_IN_QUEUE_TIME = 1.0f;

	UPROPERTY(EditAnywhere)
	TMap<EActions, ABattleActionBase*> m_Actions;

	TRingBuffer<ABattleActionBase*> m_ActionQueue;

	void ExecuteAttacks();

	void ReturnToIdle();
	
};
