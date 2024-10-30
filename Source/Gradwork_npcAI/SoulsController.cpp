// Fill out your copyright notice in the Description page of Project Settings.

#include "SoulsController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


void ASoulsController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	m_PlayerRefrence = Cast<ASoulsCharacter>(pawn);
	checkf(m_PlayerRefrence, TEXT("Invallid or missing player refrence in controller"));

	//Get local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(Subsystem, TEXT("Invallid subsystem"));

	//Wipe previous mapping and select new one
	checkf(DefaultMappingContext, TEXT("Ivallid or missing MappingsContext in soulsControllerr"));
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
	//Bind Actions to functions from the Player character
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) 
	{
		checkf(EnhancedInputComponent, TEXT("failed to load enhanced input component in souls controller"));
		// Jumping
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASoulsController::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASoulsController::StopJumping);
		}

		// Moving
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulsController::Move);

		// Looking
		if (LookAction)
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulsController::Look);

		//Battle Actions
		//Quick attack
		if (QuickAttackAction)
			EnhancedInputComponent->BindAction(QuickAttackAction, ETriggerEvent::Started, this, &ASoulsController::QuickAttack);

		//Hard attack
		if (HardAttackAction)
			EnhancedInputComponent->BindAction(HardAttackAction, ETriggerEvent::Started, this, &ASoulsController::HardAttack);

		//Throw attack
		if (ThrowAction)
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &ASoulsController::Throw);

		//Block
		if (BlockAction)
			EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ASoulsController::Block);
		//StopBlock
		if (BlockAction)
			EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Completed, this, &ASoulsController::StopBlock);

		//Heal
		if (HealAction)
			EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Started, this, &ASoulsController::Heal);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}


}

void ASoulsController::OnUnPossess()
{
	Super::OnUnPossess();
}
