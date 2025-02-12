#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_HUD.generated.h"

UCLASS()
class TASK8_API UWBP_HUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateHealthBar(float HealthPercent);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateScore(int32 NewScore);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateWaveNumber(int32 WaveNum);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateTimer(float RemainingTime);
}; 