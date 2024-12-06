#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPAction.generated.h"

UCLASS()
class GRADWORK_NPCAI_API AGOAPAction : public AActor
{
	GENERATED_BODY()
	
public:	
	AGOAPAction();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	

};
