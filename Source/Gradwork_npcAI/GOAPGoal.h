#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPGoalBase.h"

#include "BlackBoard.h"
#include "GOAPGoal.generated.h"

class WorldState;


UCLASS()
class GRADWORK_NPCAI_API AGOAPGoal : public AActor, public GOAPGoalBase
{
	GENERATED_BODY()
	
public:	
	AGOAPGoal();
	virtual void Tick(float DeltaTime) override;
	virtual bool IsVallid(BlackBoard* blackboard)const ;
	virtual void StartTimer(bool start) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Goal")
	void SetValid(bool newValue);
	UFUNCTION(BlueprintCallable, Category = "Goal")
	void SetDesiredWorldState(AWorldStateActor* desiredWorldState);
	bool CheckValidationThroughBlackboard(BlackBoard* blackboard)const;


	UPROPERTY(EditAnywhere, Category = "Goal")
	FString GoalName;
	UPROPERTY(EditAnywhere, Category = "Goal")
	float MaxGoalRunTime = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Goal")
	float MaxGoalTimeOutTime = 3.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Goal")
	bool IsTimed = false;

	UPROPERTY(EditAnywhere, Category = "Goal")
	TSoftObjectPtr < AWorldStateActor> DesiredState;
	UPROPERTY(EditAnywhere, Category = "Goal")
	TArray< FString > ValidBlackboardKey;
	UPROPERTY(EditAnywhere, Category = "Goal")
	TArray< ECompareMethode > CompareMethod;
	UPROPERTY(EditAnywhere, Category = "Goal")
	TArray< float > ValidBlackboardValue;

private:
	void UpdateTimer(float deltaTime);
	void UpdateTimeOutTimer(float deltaTime);

	float m_CurrentStoredTime = 0.0f;
};
