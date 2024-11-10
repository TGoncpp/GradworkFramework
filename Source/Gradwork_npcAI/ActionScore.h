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

private:
	float m_Weight = 0;
	UCurveFloat* m_Curve = nullptr;

};

class GRADWORK_NPCAI_API ActionScore : public AActor
{
public:
	ActionScore();

protected:
	TArray<UCurveFloat*> curves;

private:
	TArray<Score*> m_Scores;

};
