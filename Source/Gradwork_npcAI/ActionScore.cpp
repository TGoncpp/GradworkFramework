
#include "ActionScore.h"

ActionScore::ActionScore()
{
}


//-----------------------------------------------
//SCORE
//______________________________________________

Score::Score(float weight, UCurveFloat* curve)
{
	m_Weight = weight;
	m_Curve = curve;
}
