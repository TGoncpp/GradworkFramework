#include "NPC_Controller.h"
#include "UtilityAIBehaviour.h"
#include "BlackBoard.h"

ANPC_Controller::ANPC_Controller()
{
}

void ANPC_Controller::BeginPlay()
{
    Super::BeginPlay();
    m_BehaviourSystems.Empty() ;

    AIPerceptionComponent = FindComponentByClass< UAIPerceptionComponent>();
    checkf(AIPerceptionComponent, TEXT("Invallid or missing AIPerceptioncomponent found in AIController"));
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_Controller::OnPerceptionUpdated);

}

void ANPC_Controller::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_NpcRefrence = Cast<ASoulsCharacter>(InPawn);
    m_Blackboard = MakeUnique<BlackBoard>();
    
    
    GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ANPC_Controller::Block, 4.0f, false);
}

void ANPC_Controller::OnUnPossess()
{
    Super::OnUnPossess();
}

void ANPC_Controller::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!m_SelectedBehaviourSystem || !m_NpcRefrence)
        return;

    EAction newInput = m_SelectedBehaviourSystem->Execute(m_MovementVector);
    return;//->TODO:  remove when execute is fully implemented
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

void ANPC_Controller::AddUtillityToBehaviourMap(AUtilityAIBehaviour* aiBehaviour)
{
    if (aiBehaviour)
        m_SelectedBehaviourSystem = aiBehaviour;
        //m_BehaviourSystems.Add(EBehaviour::Utility, aiBehaviour);
    /*if (m_BehaviourSystems.Contains(EBehaviour::Utility))*/

    checkf(m_SelectedBehaviourSystem, TEXT("adding off behaviour system failed"));
    


    if (m_Blackboard)
        m_SelectedBehaviourSystem->AddBlackboardRefrence(m_Blackboard.Get());
    else
        GEngine->AddOnScreenDebugMessage(-1, 13.0f, FColor::Blue, TEXT("No vallid blackboard passed to aibehaviour from controller"));

}

void ANPC_Controller::AddToBlackboard(const FString& key, float value)
{
    if (m_Blackboard)
        m_Blackboard->AddBlackboardValue(key, value);
}

void ANPC_Controller::UpdateBlackboard(const FString& key, float value)
{
    if (m_Blackboard)
        m_Blackboard->UpdateKey(key, value);
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