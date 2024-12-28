#include "Logger.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

void ULogger::LogValuesOnTime(float time, float loggedValue, const FString& logInformation)
{
	FString FilePath = FPaths::ProjectDir() + TEXT("Saved/Logs/"+ logInformation + ".txt");
	FString output = FString::Printf(TEXT("%f, %f\n"), time, loggedValue);

	FFileHelper::SaveStringToFile(output, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void ULogger::LogWinLose(int win, int loss, const FString& logInformation)
{
	FString FilePath = FPaths::ProjectDir() + TEXT("Saved/Logs/" + logInformation + ".txt");
	FString output = FString::Printf(TEXT("%i, %i\n"), win, loss);

	FFileHelper::SaveStringToFile(output, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}
