#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockBackComponent.generated.h"

class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetHit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRADWORK_NPCAI_API UKnockBackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKnockBackComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RecieveDamage(const FVector& direction, float knocktime);
	UFUNCTION(BlueprintCallable, Category = "knockback")
	bool IsStunned() const { return m_WasHit; }


	UPROPERTY()
	FGetHit OnGetHit;
		
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Knockback")
	float KnockbackTime = 0.5f;

private:	
	float m_CurrentKnockTime = 0.0f;
	FVector m_NormalisedKnockDirection = { 0.0f, 0.0f, 0.0f };
	float m_FallSpeed = 1200.0f;
	UCharacterMovementComponent* m_OwnerMovementComponent = nullptr;
	bool m_WasHit = false;
};
