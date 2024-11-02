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
    AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ANPC_Controller::OnPerceptionUpdated);


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

void ANPC_Controller::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{

    for (auto& actor : UpdatedActors)
    {
        if (actor != m_NpcRefrence && Tags.Contains("Character"))
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("found the enemy"));
        }
   }
}
