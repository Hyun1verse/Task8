#include "WBP_BaseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UWBP_BaseMenu::QuitGame()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
    }
}

void UWBP_BaseMenu::ReturnToMainMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UWBP_BaseMenu::RestartGame()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        // 일시정지 해제
        PC->SetPause(false);
        
        // 마우스 커서 숨기기
        PC->SetShowMouseCursor(false);
        PC->SetInputMode(FInputModeGameOnly());
        
        // 게임 재시작
        UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
    }
}

void UWBP_BaseMenu::InitializeUI()
{
    ShowMouseCursor();
}

void UWBP_BaseMenu::ShowMouseCursor()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->SetShowMouseCursor(true);
        PC->SetInputMode(FInputModeUIOnly());
    }
}

void UWBP_BaseMenu::HideMouseCursor()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->SetShowMouseCursor(false);
        PC->SetInputMode(FInputModeGameOnly());
    }
} 