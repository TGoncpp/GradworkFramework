#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoulsCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


#include "NPC_Controller.generated.h"

class UtilityAI;

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

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UtilityAI* m_BehaviourSystem = nullptr;

private:
	//Actions
	//void Move(const FInputActionValue& Value) { m_NpcRefrence->Move(Value); };
	//void Look(const FInputActionValue& Value) { m_NpcRefrence->Look(Value); };
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

	//CharacterRefrence
	UPROPERTY()
	ASoulsCharacter* m_NpcRefrence = nullptr;

	//components
	//UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent = nullptr;
	FTimerHandle  m_Timer;

};
