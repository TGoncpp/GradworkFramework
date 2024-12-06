#include "GOAPBehaviour.h"
#include "GOAPAction.h"
#include "GOAPGoal.h"


// Sets default values
AGOAPBehaviour::AGOAPBehaviour()
{
	PrimaryActorTick.bCanEverTick = true;

}

EAction AGOAPBehaviour::Execute(FVector2D& moveInput)
{
	return EAction();
}

// Called when the game starts or when spawned
void AGOAPBehaviour::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGOAPBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

