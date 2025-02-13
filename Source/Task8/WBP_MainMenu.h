#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_BaseMenu.h"
#include "WBP_MainMenu.generated.h"

UCLASS()
class TASK8_API UWBP_MainMenu : public UWBP_BaseMenu
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable, Category = "Menu", meta=(DefaultToSelf="Target", HideSelf="true"))
    void StartGame();

    // 게임 시작 전 초기화 함수 추가
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void InitializeMenu();
}; 