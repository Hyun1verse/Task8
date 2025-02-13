#include "WBP_MainMenu.h"
#include "Kismet/GameplayStatics.h"

void UWBP_MainMenu::StartGame()
{
    if (!GetWorld()) return;  // 널 체크 추가
    
    HideMouseCursor();
    RemoveFromParent();  // UI 제거 추가
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));
}

void UWBP_MainMenu::InitializeMenu()
{
    InitializeUI();  // BaseMenu의 함수 호출
}

void UWBP_MainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    InitializeMenu();
}