#pragma once

#include "CoreMinimal.h"
UENUM(blueprintType)
enum class ECompareMethode : uint8
{
	Lower UMETA(DisplayName = "Lower"),
	Equal UMETA(DisplayName = "Equal"),
	Higher UMETA(DisplayName = "Higher")
};
struct BlackboardValue
{
	FString key;
	float value;
};

class GRADWORK_NPCAI_API BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();

	void AddBlackboardValue(const FString& key, float value);
	void UpdateKey(const FString& key, float value);
	float GetKeyValue(const FString& key) const;

private:
	TArray< BlackboardValue> m_KeyValues;
	
};
