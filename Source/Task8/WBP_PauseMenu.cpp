#include "WBP_PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void UWBP_PauseMenu::ResumeGame()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        this->RemoveFromParent();
        PC->SetPause(false);
        HideMouseCursor();  // BaseMenu의 함수 사용
    }
}