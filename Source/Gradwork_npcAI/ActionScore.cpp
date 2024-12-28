
#include "ActionScore.h"
#include "BlackBoard.h"
#include "AIBehaviourBase.h"

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

void ActionScore::CreateActionScore(TArray<float> wheights, TArray<UCurveFloat*> actionCurves, TArray<FString> blackboardKeys, EAction ActionToScoreType)
{
	checkf(wheights.Num() == actionCurves.Num(), TEXT("the arrays have to have the same aount off weights and ghraps!!!!"));

	for (int index = 0; index < actionCurves.Num(); ++index)
	{
		checkf(actionCurves.IsValidIndex(index), TEXT("Index %i is out of bounds for actionCurves"), index); 
		checkf(actionCurves[index], TEXT("actionCurve is invalid on index: %i"), index);
		checkf(wheights.IsValidIndex(index), TEXT("Index %i is out of bounds for weights"), index);
		m_Scores.Add(Score(wheights[index], blackboardKeys[index], actionCurves[index]));
	}
	m_ActionType = ActionToScoreType;
}

float ActionScore::CalculateActionScore(BlackBoard* blackboard) const
{
	checkf(m_Scores.Num() != 0, TEXT("no score is storred."));

	float totalWeight = 0;
	float totalscore = 0;
	for (const auto& score : m_Scores)
	{
		checkf(score.curve, TEXT("no curve is storred."));
		
		totalWeight += score.weight;
		totalscore += score.CalculateActionScore(blackboard);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("ToatalScore off action : %f, totalweight: %f, score : %f"), totalscore, totalWeight, totalscore / totalWeight));

	return totalscore/totalWeight;
}


EAction ActionScore::GetActionType() const
{
	return m_ActionType;
}


float Score::CalculateActionScore(BlackBoard* blackboard) const
{
	if (curve && curve->FloatCurve.GetNumKeys() > 0)
	{
		//PrintCurveKeys();
		
		float blackBoardValue = blackboard->GetKeyValue(blackboardKey);
		float curveValue = curve->GetFloatValue(blackBoardValue);
		
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("blackboardValue : %f"), blackBoardValue));
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("weighted value from curve : %f"), curveValue * weight));
		return curveValue * weight;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no vallid curve in score for calculations")));
	return 0.0f;
}

void Score::PrintCurveKeys() const
{
	const TArray<FRichCurveKey>& Keys = curve->FloatCurve.GetConstRefOfKeys();
	for (const FRichCurveKey& Key : Keys)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("Key Time: %f, Key Value: %f"), Key.Time, Key.Value));
	}
}

