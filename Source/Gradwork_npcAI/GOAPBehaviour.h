#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionScore.h"
#include "AIBehaviourBase.h"


#include "GOAPBehaviour.generated.h"

UCLASS()
class GRADWORK_NPCAI_API AGOAPBehaviour : public AActor, public AIBehaviourBase
{
	GENERATED_BODY()
	
public:	
	AGOAPBehaviour();
	virtual void Tick(float DeltaTime) override;

	virtual EAction Execute(FVector2D& moveInput)override;


protected:
	virtual void BeginPlay() override;

private:	

};
