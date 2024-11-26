// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlackBoard.h"

enum class EBehaviour
{
	Utility,
	GOAP,
	Hybrid
};

UENUM(BlueprintType)
enum class EAction : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	WalkForward UMETA(DisplayName = "WalkForward"),
	WalkSideways UMETA(DisplayName = "WalkSideways"),
	WalkBackwards UMETA(DisplayName = "WalkBackwards"),
	Block UMETA(DisplayName = "Block"),
	StopBlock UMETA(DisplayName = "StopBlock"),
	Heal UMETA(DisplayName = "Heal"),
	Throw UMETA(DisplayName = "Throw"),
	QuickAttack UMETA(DisplayName = "QuickAttack"),
	HardAttack UMETA(DisplayName = "HardAttack")
};

class GRADWORK_NPCAI_API AIBehaviourBase
{
public:
	AIBehaviourBase();
	virtual ~AIBehaviourBase();

	virtual EAction Execute(FVector2D& moveInput) = 0;

	void AddBlackboardRefrence(BlackBoard* blackboardRef);

protected:
	FVector2D m_MoveInput{ 0.0, 0.0 };
	BlackBoard* m_BlackboardRef = nullptr;

};
