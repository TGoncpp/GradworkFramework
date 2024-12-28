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
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::ControllerCreated, 1.0f, false);

}

void ASoulsGameMode::StartGame()
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::PauseGame, TimeToFinish, false);

}

void ASoulsGameMode::PauseGame()
{
	LogWinLoss();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::Quit, 2.0f, false);

}

void ASoulsGameMode::Quit()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}
