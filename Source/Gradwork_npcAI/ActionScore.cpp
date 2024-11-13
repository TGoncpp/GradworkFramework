
#include "ActionScore.h"
#include "BlackBoard.h"


ActionScore::ActionScore()
{
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

void ActionScore::Init()
{
	m_Scores.Empty();
	m_Scores.Reserve(10);
}

void ActionScore::CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves, TArray<FString> blackboardKeys)
{
	checkf(wheights.Num() == actionCurves.Num(), TEXT("the arrays have to have the same aount off weights and ghraps!!!!"));

	for (int index = 0; index < actionCurves.Num(); ++index)
	{
		checkf(actionCurves.IsValidIndex(index), TEXT("Index %i is out of bounds for actionCurves"), index); 
		checkf(actionCurves[index], TEXT("actionCurve is invalid on index: %i"), index);
		checkf(wheights.IsValidIndex(index), TEXT("Index %i is out of bounds for weights"), index);
		m_Scores.Add(Score(wheights[index], blackboardKeys[index], actionCurves[index]));
	}
	
}

float ActionScore::CalculateActionScore(BlackBoard* blackboard) const
{
	checkf(m_Scores.Num() != 0, TEXT("no score is storred."));

	float totalWeight = 0;
	float totalscore = 0;
	for (const auto& score : m_Scores)
	{
		//checkf( score.m_Curve, TEXT("INVALLID score stored in index %i"), index);
		if (!score.curve)
			return 0.0f;

		totalWeight += score.weight;

		totalscore += score.CalculateActionScore(blackboard);
	}


	return totalscore/totalWeight;
}



float Score::CalculateActionScore(BlackBoard* blackboard) const
{
	if (curve)
		return curve->GetFloatValue(blackboard->GetKeyValue(blackboardKey)) * weight;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no vallid curve in score for calculations")));
	return 0.0f;
}

