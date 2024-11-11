// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"
#include "AIBehaviourBase.h"


#include "UtilityAIBehaviour.generated.h"

UCLASS()
class GRADWORK_NPCAI_API AUtilityAIBehaviour : public AActor, public AIBehaviourBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUtilityAIBehaviour();
	virtual ~AUtilityAIBehaviour();
	virtual void Tick(float DeltaTime) override;

	virtual EAction Execute(FVector2D& moveInput)override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateActionToScore();
	UFUNCTION(BlueprintCallable)
	void AddCurvesToScoreableList(TArray<UCurveFloat*> curves, TArray<float> wheights);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCurveFloat*> actionCurves;

private:	
	TArray< ActionScore*> m_ActionScores;

};
