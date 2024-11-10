#include "NPC_Controller.h"
#include "UtilityAIBehaviour.h"


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

void ANPC_Controller::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!m_SelectedBehaviourSystem)
        return;
    EAction newInput = m_SelectedBehaviourSystem->Execute(m_MovementVector);

    switch (newInput)
    {
    case EAction::HardAttack:
        m_NpcRefrence->StopBlock();
        m_NpcRefrence->HardAttack();
        break;
    case EAction::QuickAttack:
        m_NpcRefrence->StopBlock();
        m_NpcRefrence->QuickAttack();
        break;
    case EAction::Heal:
        m_NpcRefrence->StopBlock();
        m_NpcRefrence->Heal();
        break;
    case EAction::Throw:
        m_NpcRefrence->StopBlock();
        m_NpcRefrence->ThrowAttack();
        break;
    case EAction::Walk:
        m_NpcRefrence->Move(m_MovementVector);
        break;
    case EAction::Block:
        m_NpcRefrence->Block();
        break;
    default:
        break;
    }
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

void ANPC_Controller::AddUtillityToBehaviourMap(AUtilityAIBehaviour* actionScore)
{
    m_BehaviourSystems.Add(EBehaviour::Utility, actionScore);
    if (m_BehaviourSystems.Num() == 0 || m_BehaviourSystems[EBehaviour::Utility] == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 13.0f, FColor::Blue, TEXT("failed adding off behaviour"));
        return;
    }


    m_SelectedBehaviourSystem = m_BehaviourSystems[EBehaviour::Utility];//remove this when making more systems
}


//void ANPC_Controller::AddGOAPToBehaviourMap(AIBehaviourBase* actionScore)
//{
//    m_BehaviourSystems.Add(EBehaviour::GOAP, actionScore);
//}
//
//void ANPC_Controller::AddHybridToBehaviourMap(AIBehaviourBase* actionScore)
//{
//    m_BehaviourSystems.Add(EBehaviour::Hybrid, actionScore);
//}