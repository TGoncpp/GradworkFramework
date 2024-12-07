#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPGoalBase.h"

#include "GOAPGoal.generated.h"

class WorldState;

UCLASS()
class GRADWORK_NPCAI_API AGOAPGoal : public AActor, public GOAPGoalBase
{
	GENERATED_BODY()
	
public:	
	AGOAPGoal();
	virtual void Tick(float DeltaTime) override;
	virtual bool IsVallid() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Goal")
	void SetDesiredWorldState(AWorldStateActor* desiredWorldState);
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Goal")
	bool IsGoalVallid = false;
};
