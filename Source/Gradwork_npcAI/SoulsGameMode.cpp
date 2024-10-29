#include "SoulsGameMode.h"

void ASoulsGameMode::BeginPlay()
{
	//create players 
	UGameInstance* gameInstance = GetWorld()->GetGameInstance();
	checkf(gameInstance, TEXT("gameInstance failed load"));


	
}
