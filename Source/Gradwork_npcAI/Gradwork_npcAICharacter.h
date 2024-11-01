// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "Gradwork_npcAICharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGradwork_npcAICharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	

public:
	AGradwork_npcAICharacter();
	

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	//Battle Actions
	/** fast attack input */
	virtual void QuickAttack() { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Quick"); };
			
	/** fast attack input */
	virtual void HardAttack(){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Hard"); };
			
	/** fast attack input */
	virtual void ThrowAttack(){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Throw"); };
			
	/** fast attack input */
	virtual void Block(){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Block"); };

	virtual void StopBlock() { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "StopBlock"); };

	virtual void LockOn() { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "LockOn"); };
			
	/** fast attack input */
	virtual void Heal(){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Heal"); };
			
protected:

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	bool m_IsLockOn = false;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

