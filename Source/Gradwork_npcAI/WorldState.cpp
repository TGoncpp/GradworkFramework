#include "WorldState.h"

WorldState::WorldState()
{
}

WorldState::~WorldState()
{
}

int WorldState::GetNumOffUnsatisfiedStates() const
{
	int numOffUnsatisfiedStates = 0;
	for (const bool& worldState : m_IsSatisfiedWorldStates)
	{
		if (worldState)
			numOffUnsatisfiedStates++;
	}

	return numOffUnsatisfiedStates;
}

void WorldState::UpdateWorldState(WorldState* WorldState)
{

}
