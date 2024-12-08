#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPGoalBase.h"

#include "BlackBoard.h"
#include "GOAPGoal.generated.h"

class WorldState;
UENUM(blueprintType)
enum class ECompareMethode : uint8
{
	Lower UMETA(DisplayName = "Lower"),
	Equal UMETA(DisplayName = "Equal"),
	Higher UMETA(DisplayName = "Higher")
};

UCLASS()
class GRADWORK_NPCAI_API AGOAPGoal : public AActor, public GOAPGoalBase
{
	GENERATED_BODY()
	
public:	
	AGOAPGoal();
	virtual void Tick(float DeltaTime) override;
	virtual bool IsVallid(BlackBoard* blackboard)const ;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Goal")
	void SetDesiredWorldState(AWorldStateActor* desiredWorldState);
	bool CheckValidationThroughBlackboard(BlackBoard* blackboard)const;

	UPROPERTY(EditAnywhere, Category = "Goal")
	TSoftObjectPtr < AWorldStateActor> DesiredState;
	UPROPERTY(EditAnywhere, Category = "Goal")
	FString ValidBlackboardKey;
	UPROPERTY(EditAnywhere, Category = "Goal")
	ECompareMethode CompareMethod;
	UPROPERTY(EditAnywhere, Category = "Goal")
	float ValidBlackboardValue;
};
