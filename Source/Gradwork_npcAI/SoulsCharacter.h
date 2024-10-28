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


UCLASS(Blueprintable)
class GRADWORK_NPCAI_API ASoulsCharacter : public AGradwork_npcAICharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EActions, ABattleActionBase*> m_Actions;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< ABattleActionBase*> m_ActionsArr;

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
