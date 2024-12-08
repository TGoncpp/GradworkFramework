#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOAPActionBase.h"

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
	virtual void UpdateAction() override;
	virtual EAction GetActionInput()const override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GOAPAction")
	void UpdateActionImplementation();
	
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	EAction ActionInput;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TSoftObjectPtr <AWorldStateActor> DesiredState = nullptr;
	UPROPERTY(EditAnywhere, Category = "GOAPAction")
	TSoftObjectPtr <AWorldStateActor>  SatisfiesState = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "GOAPAction")
	bool IsActionFinished = false;

};
