#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"

/**
 * 
 */
class Score
{
public:
	Score(float weight, UCurveFloat* curve);
	float CalculateActionScore(float Xvalue) const;

	float m_Weight = 0;
	UCurveFloat* m_Curve = nullptr;

};

class GRADWORK_NPCAI_API ActionScore : public AActor
{
public:
	ActionScore();
	~ActionScore();

	ActionScore* CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves);
	float CalculateActionScore() const;

private:
	TArray<Score*> m_Scores;

};
