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
enum class EAction : uint8;
class UHealthComponent;
class UStaminaComponent;
class UKnockBackComponent;


UCLASS(Blueprintable)
class GRADWORK_NPCAI_API ASoulsCharacter : public AGradwork_npcAICharacter
{
	GENERATED_BODY()

public:
	ASoulsCharacter();
	virtual void Tick(float DeltaTime) override;

	void RemoveActionsThatAreToLongInQueue();
	virtual void BeginPlay() override;


#pragma region Getters

	UFUNCTION(BlueprintCallable, Category = "Refrences")
	UHealthComponent* GetHealthComponentRef ()const;
	UFUNCTION(BlueprintCallable, Category = "Refrences")
	UStaminaComponent* GetStaminaComponentRef()const;
	UFUNCTION(BlueprintCallable, Category = "Refrences")
	UKnockBackComponent* GetKnockbackComponentRef()const;
	UFUNCTION(BlueprintCallable, Category = "Refrences")
	ABattleActionBase* GetCurrentAction()const;

#pragma endregion Getters

#pragma region Battle Actions

	virtual void QuickAttack()override;
	virtual void HardAttack()override;
	virtual void ThrowAttack()override;
	virtual void Block()override;				
	virtual void StopBlock()override;
	virtual void Heal()override;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void LockOn()override;
	
#pragma endregion Battle Actions

	UFUNCTION(BlueprintImplementableEvent)
	void Ragdoll();
	UFUNCTION(BlueprintImplementableEvent)
	void RiseAgain();

	UFUNCTION(BlueprintCallable)
	void FoundTarget(ASoulsCharacter* target);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 TArray<ABattleActionBase*> m_Actions;
	//TMap<EAction, ABattleActionBase*> m_Actions;
protected:

	UFUNCTION(BlueprintCallable)
	void AddAction(ABattleActionBase* newAction);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Debug")
	ASoulsCharacter* m_Target = nullptr;

#pragma region components
	UPROPERTY(VisibleAnywhere)
	UHealthComponent* m_HealthComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaminaComponent* m_StaminaComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	UKnockBackComponent* m_KnockbackComponent = nullptr;
#pragma endregion components

private:
	void ExecuteAttacks();
	void ReturnToIdle();
	UFUNCTION()
	void ResetQueue();
	void LookAtTarget();

	//DebugFunctions
	void PrintQueue();
	ABattleActionBase* FindActionOffType(EAction actionType);


	FTimerHandle  m_Timer;
	bool m_IsIdle = true;
	const int MAX_QUEUESIZE = 5;
	const float MAX_IN_QUEUE_TIME = 1.0f;
	TRingBuffer< ABattleActionBase*> m_ActionQueue;
	ABattleActionBase* m_ActivatedAction = nullptr;
};
