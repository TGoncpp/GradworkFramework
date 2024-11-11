
#include "ActionScore.h"



ActionScore::ActionScore()
{
	m_Scores.Empty();
	m_Scores.Reserve(10);
}

ActionScore::~ActionScore()
{
	//for (int index = 0; index < m_Scores.Num(); ++index)
	//{
	//	if (m_Scores[index] )
	//	{
	//		delete m_Scores[index];
	//		m_Scores[index] = nullptr;
	//	}
	//}
	m_Scores.Empty();

}

ActionScore* ActionScore::CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves)
{
	checkf(wheights.Num() == actionCurves.Num(), TEXT("the arrays have to have the same aount off weights and ghraps!!!!"));

	for (int index = 0; index < actionCurves.Num(); ++index)
	{
		checkf(actionCurves.IsValidIndex(index), TEXT("Index %i is out of bounds for actionCurves"), index); 
		checkf(actionCurves[index], TEXT("actionCurve is invalid on index: %i"), index);
		checkf(wheights.IsValidIndex(index), TEXT("Index %i is out of bounds for weights"), index);
		m_Scores.Add(Score(wheights[index], actionCurves[index]));
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
		//checkf( score, TEXT("INVALLID score stored in index %i"), index);
		totalWeight += score.m_Weight;

		totalscore += score.CalculateActionScore(0.5f); //change this magic number to a blackboard value
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
	if (m_Curve)
		return m_Curve->GetFloatValue(Xvalue) * m_Weight;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no vallid curve in score for calculations")));
	return 0.0f;
}

