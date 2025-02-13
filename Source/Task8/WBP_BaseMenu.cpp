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