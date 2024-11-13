#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"

/**
 * 
 */
class BlackBoard;

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

	void CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves, TArray<FString> blackboardKeys);
	float CalculateActionScore(BlackBoard* blackboard) const;

private:

	
	TArray<Score> m_Scores;

};
