#include "SoulsGameMode.h"
#include "Kismet/GameplayStatics.h"

float ASoulsGameMode::GetSettedGameTime() const
{
	return TimeToFinish;
}

void ASoulsGameMode::BeginPlay()
{
	//create players 
	UGameInstance* gameInstance = GetWorld()->GetGameInstance();
	checkf(gameInstance, TEXT("gameInstance failed load"));

	CreateHud();
	StartGame();
	GetWorld()->GetTimerManager().SetTimer(m_Timer2, this, &ASoulsGameMode::ControllerCreated, 1.0f, false);

}

void ASoulsGameMode::StartGame()
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::PauseGame, TimeToFinish, false);

}

void ASoulsGameMode::PauseGame()
{
	LogWinLoss();
	SwitchBehaviourToGOAP();
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::Quit, TimeToFinish + TimeBetweenSytems, false);

	//UGameplayStatics::SetGamePaused(GetWorld(), true);

}

void ASoulsGameMode::Quit()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "quit is called");
	LogWinLoss();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}
