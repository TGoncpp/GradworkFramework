// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAIBehaviour.h"
#include "BlackBoard.h"

// Sets default values
AUtilityAIBehaviour::AUtilityAIBehaviour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AUtilityAIBehaviour::~AUtilityAIBehaviour()
{
	
}

// Called when the game starts or when spawned
void AUtilityAIBehaviour::BeginPlay()
{
	Super::BeginPlay();

	CreateActionToScore();
	
}

void AUtilityAIBehaviour::BeginDestroy()
{
	Super::BeginDestroy();

	m_ActionScores.Empty();
}

void AUtilityAIBehaviour::AddCurvesToScoreableList(TArray<UCurveFloat*> curves, TArray<float> wheights, TArray<FString> blackboardKeys)
{
	m_ActionScores.Add(MakeUnique< ActionScore>());
	m_ActionScores.Last()->Init();
	m_ActionScores.Last()->CreateActionScore(wheights, curves, blackboardKeys);

}

// Called every frame
void AUtilityAIBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EAction AUtilityAIBehaviour::Execute(FVector2D& moveInput)
{
	
	if (m_ActionScores.Num()> 0 && m_ActionScores[0] != nullptr && m_BlackboardRef)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("calculated value off action index 0 : %f"),m_ActionScores[0]->CalculateActionScore(m_BlackboardRef)));
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no entery in map off behaviours : %i"),m_ActionScores.Num()));


	return EAction();
}

