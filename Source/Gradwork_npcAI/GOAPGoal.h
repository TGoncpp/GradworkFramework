#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPGoal.generated.h"

class WorldState;

UCLASS()
class GRADWORK_NPCAI_API AGOAPGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGOAPGoal();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	WorldState* m_DiseredState;
	FString M_NameOfGoal{ "default" };
};
