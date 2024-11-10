// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"


#include "UtilityAIBehaviour.generated.h"

UCLASS()
class GRADWORK_NPCAI_API AUtilityAIBehaviour : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUtilityAIBehaviour();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCurveFloat*> curves;

private:	
	TArray< ActionScore*> m_ActionScore;

};
