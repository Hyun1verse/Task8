#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_BaseMenu.h"
#include "WBP_GameOver.generated.h"

UCLASS()
class TASK8_API UWBP_GameOver : public UWBP_BaseMenu
{
    GENERATED_BODY()

public:
    // 최종 점수 표시 함수
    UFUNCTION(BlueprintImplementableEvent, Category = "Menu")
    void DisplayFinalScore(int32 Score);
}; 