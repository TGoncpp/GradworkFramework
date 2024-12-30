// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRADWORK_NPCAI_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SuccesfullExecution(float cost, bool intenseAction = false);
	void ClearStamina();
	void FullStamina();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetStaminaPercentage() const { return m_Stamina / MAX_STAMINA; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float m_Stamina = 0.0f;
private:	
	const float MAX_STAMINA = 100.0f;
	const float	REGENERATION_RATE = 5.0f;

	void Regenerate(float deltaTime);
		
};
