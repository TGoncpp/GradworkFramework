#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"

/**
 * 
 */
class BlackBoard;
enum class EAction : uint8;

struct Score
{
	float weight = 0;
	FString blackboardKey;
	UCurveFloat* curve = nullptr;

	float CalculateActionScore(BlackBoard* blackboard) const;
};

class GRADWORK_NPCAI_API ActionScore 
{
public:
	ActionScore();
	~ActionScore();

	void Init();

	void CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves, TArray<FString> blackboardKeys, EAction AttackToScoreType);
	float CalculateActionScore(BlackBoard* blackboard) const;

private:

	EAction m_ActionType;
	TArray<Score> m_Scores;

};
