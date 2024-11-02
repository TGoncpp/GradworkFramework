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


protected:
	virtual void BeginPlay() override;
	
	UtilityAI* m_BehaviourSystem = nullptr;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	//Actions
	void Move(const FInputActionValue& Value) { m_NpcRefrence->Move(Value); };
	void Look(const FInputActionValue& Value) { m_NpcRefrence->Look(Value); };
	void QuickAttack() { m_NpcRefrence->QuickAttack(); };
	void HardAttack() { m_NpcRefrence->HardAttack(); };
	void Heal() { m_NpcRefrence->Heal(); };
	void Block() { m_NpcRefrence->Block(); };
	void StopBlock() { m_NpcRefrence->StopBlock(); };
	void Throw() { m_NpcRefrence->ThrowAttack(); };
	void LockOn() { m_NpcRefrence->LockOn(); };

	//Perception
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	//CharacterRefrence
	UPROPERTY()
	ASoulsCharacter* m_NpcRefrence = nullptr;

	//components
	//UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent = nullptr;
	FTimerHandle  m_Timer;

};
