#include "NPC_Controller.h"
#include "UtilityAIBehaviour.h"
#include "GOAPBehaviour.h"
#include "BlackBoard.h"

ANPC_Controller::ANPC_Controller()
{
}

void ANPC_Controller::BeginPlay()
{
    Super::BeginPlay();
    //m_BehaviourSystems.Empty() ;

    AIPerceptionComponent = FindComponentByClass< UAIPerceptionComponent>();
    checkf(AIPerceptionComponent, TEXT("Invallid or missing AIPerceptioncomponent found in AIController"));
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_Controller::OnPerceptionUpdated);

}

void ANPC_Controller::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_NpcRefrence = Cast<ASoulsCharacter>(InPawn);
    m_Blackboard = MakeUnique<BlackBoard>();
    
    //Test line for block command
    //GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ANPC_Controller::Block, 4.0f, false);
}

void ANPC_Controller::OnUnPossess()
{
    Super::OnUnPossess();
}

void ANPC_Controller::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //when switching between systemns, stop executing
    if (!IsExecuting)
        return;

    if (!m_SelectedBehaviourSystem || !m_NpcRefrence)
        return;

    if (!m_LockedOnPlayer)
    {
        LockOn();
        m_LockedOnPlayer = true;
    }

    //Get input from the active DecisionMaking algorithm 
    EAction newInput = m_SelectedBehaviourSystem->Execute(m_MovementVector);

    switch (newInput)
    {
    case EAction::Idle:
        //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("selected Idle action"));
        break;
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
    case EAction::WalkBackwards:
        m_MovementVector = { 0.0f, -1.0f };
        m_NpcRefrence->Move(m_MovementVector);
        break;
    case EAction::WalkForward:
        m_MovementVector = { 0.0f, 1.0f };
        m_NpcRefrence->Move(m_MovementVector);
        break;
    case EAction::WalkSideways:
        m_MovementVector = { -1.0f, 0.0f };
        m_NpcRefrence->Move(m_MovementVector);
        break;
    case EAction::Block:
        m_NpcRefrence->Block();
        break;
    case EAction::StopBlock:
        m_NpcRefrence->StopBlock();
        break;
    default:
        break;
    }
}

ASoulsCharacter* ANPC_Controller::GetControlledNpcRef() const
{
    return m_NpcRefrence;
}



void ANPC_Controller::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("update perception"));  
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

void ANPC_Controller::AddGOAPToBehaviourMap(AGOAPBehaviour* GOAPBehaviour)
{
    if (GOAPBehaviour)
    {
        m_SelectedBehaviourSystem = GOAPBehaviour;
        m_GOAPBehaviourSystem = GOAPBehaviour;
    }

    checkf(m_SelectedBehaviourSystem, TEXT("adding off behaviour system failed"));


    if (m_Blackboard)
        m_SelectedBehaviourSystem->AddBlackboardRefrence(m_Blackboard.Get());
    else
        GEngine->AddOnScreenDebugMessage(-1, 13.0f, FColor::Blue, TEXT("No vallid blackboard passed to aibehaviour from controller"));

}

void ANPC_Controller::AddToBlackboard(float value, const FString& key)
{
    if (m_Blackboard)
        m_Blackboard->AddBlackboardValue(key, value);
}

void ANPC_Controller::UpdateBlackboard(float value, const FString& key)
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