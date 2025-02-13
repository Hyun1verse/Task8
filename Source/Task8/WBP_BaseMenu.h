#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_BaseMenu.generated.h"

UCLASS()
class TASK8_API UWBP_BaseMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void QuitGame();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ReturnToMainMenu();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void RestartGame();

    // 공통 UI 초기화 함수 추가
    UFUNCTION(BlueprintCallable, Category = "Menu")
    virtual void InitializeUI();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ShowMouseCursor();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void HideMouseCursor();
}; 