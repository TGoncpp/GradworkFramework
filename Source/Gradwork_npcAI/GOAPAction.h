#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPActionBase.h"
#include "BlackBoard.h"

#include "GOAPAction.generated.h"



UCLASS()
class GRADWORK_NPCAI_API AGOAPAction : public AActor, public GOAPActionBase
{
	GENERATED_BODY()
	
public:	
	AGOAPAction();
	virtual ~AGOAPAction()= default;
	virtual void Tick(float DeltaTime) override;

	virtual bool IsFinished()const override;
	virtual void UpdateAction(BlackBoard* blackboard) override;
	virtual EAction GetActionInput()const override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GOAPAction")
	void UpdateActionImplementation();
	
	//Action state
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	EAction ActionInput;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TSoftObjectPtr <AWorldStateActor> DesiredState = nullptr;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TSoftObjectPtr <AWorldStateActor>  SatisfiesState = nullptr;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	float Cost = 0.0f;

	//Action validation state
	UPROPERTY(BlueprintReadWrite, Category = "GOAPAction")
	bool IsActionFinished = false;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TArray<FString> UpdateBlackboardKey;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TArray<float> UpdateBlackboardValue;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TArray<ECompareMethode> UpdateCompareMethode;

private:
	bool CompareBlackboardValues(BlackBoard* blackboard, const FString& key, float comparedValue, ECompareMethode compareMethode);
	float CalculateHeuristic() const;


};
