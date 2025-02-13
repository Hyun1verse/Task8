#include "WBP_MainMenu.h"
#include "Kismet/GameplayStatics.h"

void UWBP_MainMenu::StartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));
}