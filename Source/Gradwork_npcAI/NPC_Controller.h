#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoulsCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIBehaviourBase.h"


#include "NPC_Controller.generated.h"

class BlackBoard;

UCLASS()
class GRADWORK_NPCAI_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	ANPC_Controller();

	UFUNCTION(BlueprintCallable, Category = "AI-Input")
	void StopAIMovement();

	UFUNCTION(BlueprintCallable, Category = "AI-Input")
	void LockOn() { m_NpcRefrence->LockOn(); };

	UFUNCTION(BlueprintCallable, Category = "AI-Input")
	void AddUtillityToBehaviourMap(AUtilityAIBehaviour* actionScore);

	UFUNCTION(BlueprintCallable, Category = "blackboard")
	void AddToBlackboard( float value, const FString& key);
	UFUNCTION(BlueprintCallable, Category = "blackboard")
	void UpdateBlackboard(float value, const FString& key);
	
	//UFUNCTION(BlueprintCallable, Category = "AI-Input")
	//void AddGOAPToBehaviourMap(AIBehaviourBase* actionScore);
	//
	//UFUNCTION(BlueprintCallable, Category = "AI-Input")
	//void AddHybridToBehaviourMap(AIBehaviourBase* actionScore);

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Refrences")
	ASoulsCharacter* GetControlledNpcRef()const;
	//void SelectBehaviourSystem(const EBehaviour& selectedState) { m_SelectedBehaviourSystem = m_BehaviourSystems[selectedState]; }

private:
	//Actions
	void QuickAttack() { m_NpcRefrence->QuickAttack(); };
	void HardAttack() { m_NpcRefrence->HardAttack(); };
	void Heal() { m_NpcRefrence->Heal(); };
	void Block() { m_NpcRefrence->Block(); };
	void StopBlock() { m_NpcRefrence->StopBlock(); };
	void Throw() { m_NpcRefrence->ThrowAttack(); };

	//movement
	void SetMovement(const FVector2D& newMoveInput);
	void UpdateMovement()const;

	FVector2D m_MovementVector = FVector2D{0.0, 0.0};

	//Perception
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//components
	//UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent = nullptr;
	FTimerHandle  m_Timer;

	//CharacterRefrence
	UPROPERTY()
	ASoulsCharacter* m_NpcRefrence = nullptr;

	//behavioursystems
	//TMap< EBehaviour,AIBehaviourBase*> m_BehaviourSystems;
	AUtilityAIBehaviour* m_SelectedBehaviourSystem = nullptr;
	TUniquePtr< BlackBoard> m_Blackboard = nullptr;
	bool m_LockedOnPlayer = false;
};
