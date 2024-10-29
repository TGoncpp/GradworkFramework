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

UCLASS(Blueprintable, BlueprintType)
class GRADWORK_NPCAI_API ABattleActionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleActionBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Execute();
	float GetExecutionTime() const { return ExecutionTime; }
	void EnQueue(float timePermitedInQueue);
	bool ToLongInQueue(float deltaTime);
	FString GetActionName() const { return ActionName; }
	EActions GetActionType() const { return m_ActionType; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActions m_ActionType = EActions::Quick;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExecutionTime{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost{ 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName{ "default"};

private:
	float M_InQueueTimeLeft{ 0.0f };
};
