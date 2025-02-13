#include "WBP_PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void UWBP_PauseMenu::RestartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}

void UWBP_PauseMenu::ResumeGame()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        this->RemoveFromParent();
        PC->SetPause(false);
        PC->SetShowMouseCursor(false);
        PC->SetInputMode(FInputModeGameOnly());
    }
}