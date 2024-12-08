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
	Fight UMETA(DisplayName = "Fight"),
	Dodge UMETA(DisplayName = "Dodge"),
	Heal UMETA(DisplayName = "Heal"),
	Counter UMETA(DisplayName = "Counter"),

};



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
	void UpdateWorldState(AWorldStateActor* WorldState);
	EGoal GetGoalState()const;
	EAction GetActionState()const;
	EAction GetOpponentActionState()const;
	ECondition GetConditionState()const;
	ECondition GetOpponentConditionState()const;
	EDistance GetDistanceState()const;
	bool IsWorldStateEqualOnIndex(AWorldStateActor* otherWorldState, int index)const;
	bool IsWorldStateActiveAtIndex(int index)const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	TArray<bool> m_IsActiveWorldStates;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EGoal m_GoalState;                  //index =0 -> will always be the desired state off a Goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EAction m_ActionState;              //index =1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EAction m_OpponentActionState;      //index =2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	ECondition m_ConditionState;        //index =3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	ECondition m_OpponentConditionState;//index =4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldState")
	EDistance m_DistanceToOpponentState;//index =5

};
