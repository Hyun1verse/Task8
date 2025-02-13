#include "WBP_GameOver.h"
#include "Kismet/GameplayStatics.h"

void UWBP_GameOver::RestartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}