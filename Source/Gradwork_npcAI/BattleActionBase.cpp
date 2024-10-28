// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleActionBase.h"

// Sets default values
ABattleActionBase::ABattleActionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABattleActionBase::EnQueue(float timePermitedInQueue)
{
	M_InQueueTimeLeft = timePermitedInQueue;
}

bool ABattleActionBase::ToLongInQueue(float deltaTime)
{
	M_InQueueTimeLeft -= deltaTime;

	return M_InQueueTimeLeft <= 0.f;
}

// Called when the game starts or when spawned
void ABattleActionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleActionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

