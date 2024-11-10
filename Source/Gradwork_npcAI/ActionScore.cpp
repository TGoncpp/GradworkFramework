
#include "ActionScore.h"



ActionScore::ActionScore()
{
	m_Scores.Empty();
}

ActionScore* ActionScore::CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves)
{
	if (wheights.Num() != actionCurves.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,TEXT("the arrays have to have the same aount off elements!!!!"));
		return nullptr;
	}

	m_Scores.Reserve(10);
	for (int index = 0; index < actionCurves.Num(); ++index)
	{
		checkf(actionCurves[index], TEXT("actioncurve is invallid on index : %i"), index);
		m_Scores.Add(new Score(wheights[index], actionCurves[index]));
	}
	
	return this;
}

float ActionScore::CalculateActionScore() const
{
	float totalWeight = 0;
	float totalscore = 0;
	for (const auto& score : m_Scores)
	{
		totalWeight += score->m_Weight;
		totalscore += score->CalculateActionScore(0.5f); //change this magic number to a blackboard value
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

