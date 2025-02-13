#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_BaseMenu.h"
#include "WBP_PauseMenu.generated.h"

UCLASS()
class TASK8_API UWBP_PauseMenu : public UWBP_BaseMenu
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void RestartGame();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ResumeGame();
}; 