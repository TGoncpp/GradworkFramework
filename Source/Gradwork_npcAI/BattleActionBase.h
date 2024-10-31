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

	void AddParent(AActor* parent);

	UFUNCTION(BlueprintImplementableEvent)
	void Execute();
	UFUNCTION(BlueprintImplementableEvent)
	void DeActivate();
	
	//Queue functions
	void EnQueue(float timePermitedInQueue);
	bool ToLongInQueue(float deltaTime);

	//stamina
	bool HasSufficentStamina() const;

	//getters
	float GetExecutionTime() const { return ExecutionTime; }
	FString GetActionName() const { return ActionName; }
	EActions GetActionType() const { return m_ActionType; }
	UFUNCTION(BlueprintCallable, Category = "Heal")
	AActor* GetParent() const { return m_ParentActor; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActions m_ActionType = EActions::Quick;

	//is set only in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	bool BlockIsActive = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExecutionTime{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost{ 35.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage{ 15.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockTime{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName{ "default"};

private:
	float M_InQueueTimeLeft{ 0.0f };
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	class UCapsuleComponent* m_TriggerCapsule = nullptr;
	AActor* m_ParentActor = nullptr;
};
