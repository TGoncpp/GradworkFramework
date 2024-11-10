// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoulsCharacter.h"

#include "SoulsController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
//class ASoulsCharacter;

UCLASS()
class GRADWORK_NPCAI_API ASoulsController : public APlayerController
{
	GENERATED_BODY()

public:

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

	//Input Actions
#pragma region Actions
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QuickAttackAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HardAttackAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BlockAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HealAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction = nullptr;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction = nullptr;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LockOnAction = nullptr;

#pragma endregion Actions

protected:
	virtual void OnPossess(APawn* pawn)override;
	virtual void OnUnPossess()override;
	
private:
	//CharacterRefrence
	UPROPERTY()
	ASoulsCharacter* m_NpcRefrence = nullptr;

#pragma region ActionFunctions

	void Jump() { m_NpcRefrence->Jump(); };
	void StopJumping() { m_NpcRefrence->StopJumping(); };
	void Move(const FInputActionValue& Value) { m_NpcRefrence->Move(Value); };
	void Look(const FInputActionValue& Value) { m_NpcRefrence->Look(Value); };
	void LockOn() { m_NpcRefrence->LockOn(); };

	void QuickAttack() { m_NpcRefrence->QuickAttack(); };
	void HardAttack() { m_NpcRefrence->HardAttack(); };
	void Heal() { m_NpcRefrence->Heal(); };
	void Block() { m_NpcRefrence->Block(); };
	void StopBlock() { m_NpcRefrence->StopBlock(); };
	void Throw() { m_NpcRefrence->ThrowAttack(); };

#pragma endregion ActionFunctions


};
