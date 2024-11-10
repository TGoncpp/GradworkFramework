// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EBehaviour
{
	Utility,
	GOAP,
	Hybrid
};

enum class EAction
{
	Walk,
	Block,
	Heal,
	Throw,
	QuickAttack,
	HardAttack
};

class GRADWORK_NPCAI_API AIBehaviourBase
{
public:
	AIBehaviourBase();
	~AIBehaviourBase();

	virtual EAction Execute(FVector2D& moveInput) = 0;

protected:
	FVector2D m_MoveInput{ 0.0, 0.0 };
};
