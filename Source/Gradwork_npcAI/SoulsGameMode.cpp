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
}

void ASoulsGameMode::StartGame()
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ASoulsGameMode::PauseGame, TimeToFinish, false);

}

void ASoulsGameMode::PauseGame()
{
	LogWinLoss();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
