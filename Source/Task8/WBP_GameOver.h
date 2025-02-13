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
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void RestartGame();
}; 