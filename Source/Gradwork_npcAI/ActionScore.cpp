
#include "ActionScore.h"



ActionScore::ActionScore()
{
	m_Scores.Empty();
	m_Scores.Reserve(10);
}

ActionScore* ActionScore::CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves)
{
	checkf(wheights.Num() == actionCurves.Num(), TEXT("the arrays have to have the same aount off weights and ghraps!!!!"));

	for (int index = 0; index < actionCurves.Num(); ++index)
	{
		checkf(actionCurves[index], TEXT("actioncurve is invallid on index : %i"), index);
		m_Scores.Add(new Score(wheights[index], actionCurves[index]));
	}
	
	return this;
}

float ActionScore::CalculateActionScore() const
{
	checkf(m_Scores.Num() != 0, TEXT("no score is storred."));

	float totalWeight = 0;
	float totalscore = 0;
	int index = 0;
	for (const auto& score : m_Scores)
	{
		checkf( score, TEXT("INVALLID score stored in index %i"), index);
		totalWeight += score->m_Weight;
		totalscore += score->CalculateActionScore(0.5f); //change this magic number to a blackboard value
		index++;
	}


	return totalscore/totalWeight;
}


//-----------------------------------------------
//SCORE
//______________________________________________

Score::Score(float weight, UCurveFloat* curve)
{
	m_Weight = weight;
	m_Curve = curve;
}

float Score::CalculateActionScore(float Xvalue) const
{
	return m_Curve->GetFloatValue(Xvalue) * m_Weight;
}

