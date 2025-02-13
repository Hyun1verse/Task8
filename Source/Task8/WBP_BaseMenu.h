#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_BaseMenu.generated.h"

UCLASS()
class TASK8_API UWBP_BaseMenu : public UUserWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void QuitGame();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ReturnToMainMenu();
}; 