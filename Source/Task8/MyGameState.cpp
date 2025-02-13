#include "MyGameState.h"
#include "Net/UnrealNetwork.h"
#include "MyGameMode.h"

AMyGameState::AMyGameState()
{
    CurrentWave = 0;
    Score = 0;
    RemainingTime = 0.0f;
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyGameState, CurrentWave);
    DOREPLIFETIME(AMyGameState, Score);
    DOREPLIFETIME(AMyGameState, RemainingTime);
}

void AMyGameState::AddScore(int32 Points)
{
    Score += Points;
    
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateScore(Score);
    }
}

void AMyGameState::SetCurrentWave(int32 NewWave)
{
    CurrentWave = NewWave;
    
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateWaveNumber(CurrentWave);
    }
}

void AMyGameState::SetRemainingTime(float NewTime)
{
    RemainingTime = NewTime;
    
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateTimer(RemainingTime);
    }
}

void AMyGameState::OnRep_CurrentWave()
{
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateWaveNumber(CurrentWave);
    }
}

void AMyGameState::OnRep_Score()
{
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateScore(Score);
    }
}

