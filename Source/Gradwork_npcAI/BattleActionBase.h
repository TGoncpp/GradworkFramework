// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BattleActionBase.generated.h"

class UCharacterMovementComponent;
enum class EAction : uint8;

UCLASS(Blueprintable, BlueprintType)
class GRADWORK_NPCAI_API ABattleActionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleActionBase();
	virtual void Tick(float DeltaTime) override;

	void AddParent(AActor* parent);
	void AddParentMovementComp(UCharacterMovementComponent* parentMoveComp);

	UFUNCTION(BlueprintImplementableEvent)
	void Execute();
	UFUNCTION(BlueprintImplementableEvent)
	void DeActivate();
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void SimulateHitActor(AActor* hitAtor);
	
	//Queue functions
	void EnQueue(float timePermitedInQueue);
	bool ToLongInQueue(float deltaTime);

	//stamina
	bool HasSufficentStamina() const;

	//getters
	float GetExecutionTime() const { return ExecutionTime; }
	UFUNCTION(BlueprintCallable, Category = "Actions")
	EAction GetActionType() const { return m_ActionType; }
	UFUNCTION(BlueprintCallable, Category = "Actions")
	AActor* GetParent() const { return m_ParentActor; }
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsBlocking() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsHealing() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsThrowing() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsAttacking() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsQuickAttacking() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsStraightForwardAttacking() const;	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAction m_ActionType;
	//is set only in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	bool BlockIsActive = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "actions")
	UCharacterMovementComponent* GetParentMovementComp()const;


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
	float m_InQueueTimeLeft{ 0.0f };
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

	class UCapsuleComponent* m_TriggerCapsule = nullptr;
	AActor* m_ParentActor = nullptr;
	UCharacterMovementComponent* m_ParentMovementComp = nullptr;
};
