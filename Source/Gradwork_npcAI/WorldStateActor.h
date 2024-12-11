#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WorldStateActor.generated.h"

enum class EAction : uint8;

UENUM(BlueprintType)
enum class ECondition : uint8
{
	Perfect UMETA(DisplayName = "Perfect"),
	LowHP UMETA(DisplayName = "LowHP"),
	LowSP UMETA(DisplayName = "LowSP"),
	Low UMETA(DisplayName = "Low"),
	HighSP UMETA(DisplayName = "HighSP"),
	HighHP UMETA(DisplayName = "HighHP"),

};

UENUM(BlueprintType)
enum class EDistance : uint8
{
	Close UMETA(DisplayName = "Close"),
	OutOfRange UMETA(DisplayName = "OutOfRange"),
	HealDistance UMETA(DisplayName = "HealDistance"),

};

UENUM(BlueprintType)
enum class EGoal : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Fight UMETA(DisplayName = "Fight"),
	Dodge UMETA(DisplayName = "Dodge"),
	Heal UMETA(DisplayName = "Heal"),
	Counter UMETA(DisplayName = "Counter"),

};

class BlackBoard;

UCLASS(BlueprintType)
class GRADWORK_NPCAI_API AWorldStateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldStateActor();
	virtual void Tick(float DeltaTime) override;

	int GetNumOffUnsatisfiedStates()const;
	int GetNumOffAllStates()const;
	TArray<int> GetIndexOffAllActiveStates()const;
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	void UpdateWorldState( AActor* player, AActor* npc);
	EGoal GetGoalState()const;
	void SetGoalState(EGoal newGoal);
	EAction GetActionState()const;
	void SetActionState(EAction newAction);
	EAction GetOpponentActionState()const;
	void SetOpponentActionState(EAction newAction);
	ECondition GetConditionState()const;
	void SetConditionState(ECondition newCondition);
	ECondition GetOpponentConditionState()const;
	void SetOpponentConditionState(ECondition newCondition);
	EDistance GetDistanceState()const;
	void SetDistanceState(EDistance newDistance);
	bool IsWorldStateEqualOnIndex(AWorldStateActor* otherWorldState, int index)const;
	void CompareWithCurrentState(AWorldStateActor* currentWorldState, AWorldStateActor* otherWorldState)const;
	bool IsWorldStateActiveAtIndex(int index)const;
	void SetDesiredIndex(int index, AWorldStateActor* newWorldState);
	void ResetWorldState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	TArray<bool> m_IsActiveWorldStates{false, false, false, false, false, false};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EGoal m_GoalState = EGoal::Idle;                  //index =0 -> will always be the desired state off a Goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EAction m_ActionState;                            //index =1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EAction m_OpponentActionState;                    //index =2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	ECondition m_ConditionState = ECondition::Perfect;        //index =3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	ECondition m_OpponentConditionState = ECondition::Perfect;//index =4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EDistance m_DistanceToOpponentState = EDistance::OutOfRange;//index =5

private:
	const float m_DistanceOfReach = 150.0f;
	const float m_DistanceOfHeal = 650.0f;
	const float m_MinValue = 0.4f;
	const float m_HighValue = 0.7f;
};
