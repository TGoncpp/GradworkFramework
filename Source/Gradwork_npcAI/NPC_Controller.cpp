#include "NPC_Controller.h"
#include "UtilityAI.h"


ANPC_Controller::ANPC_Controller()
{
}

void ANPC_Controller::BeginPlay()
{
    Super::BeginPlay();

    AIPerceptionComponent = FindComponentByClass< UAIPerceptionComponent>();
    checkf(AIPerceptionComponent, TEXT("Invallid or missing AIPerceptioncomponent found in AIController"));
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_Controller::OnPerceptionUpdated);


}

void ANPC_Controller::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_NpcRefrence = Cast<ASoulsCharacter>(InPawn);
    
    GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ANPC_Controller::Block, 4.0f, false);
}

void ANPC_Controller::OnUnPossess()
{
    Super::OnUnPossess();
}

void ANPC_Controller::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("update perception"));

    
}

void ANPC_Controller::SetMovement(const FVector2D& newMoveInput)
{
    m_MovementVector = newMoveInput;
    m_NpcRefrence->Move(m_MovementVector);

}

void ANPC_Controller::UpdateMovement() const
{
    m_NpcRefrence->Move(m_MovementVector);
}

void ANPC_Controller::StopAIMovement()
{
    m_MovementVector = { 0.0, 0.0 };
}
