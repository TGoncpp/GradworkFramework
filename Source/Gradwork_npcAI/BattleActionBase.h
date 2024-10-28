// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BattleActionBase.generated.h"

UENUM()
enum class EActions
{
	Quick,
	Hard,
	Throw,
	Block,
	Heal
};

UCLASS()
class GRADWORK_NPCAI_API ABattleActionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleActionBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Execute();
	float GetExecutionTime() const { return m_ExecutionTime; }
	void EnQueue(float timePermitedInQueue);
	bool ToLongInQueue(float deltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	float m_ExecutionTime{ 1.0f };
	UPROPERTY(BlueprintReadWrite)
	float m_Cost{ 0.0f };

private:
	float M_InQueueTimeLeft{ 0.0f };
};
