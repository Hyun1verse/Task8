#include "MyGameMode.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Blueprint/UserWidget.h"
#include "WBP_HUD.h"  // UI 위젯 블루프린트를 위한 헤더

AMyGameMode::AMyGameMode()
{
    PreWaveDelay = 1.0f;  // 1초 대기
    WaveDuration = 30.0f;  // 30초
    CurrentWave = 0;  // 웨이브 0부터 시작
}

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 플레이어 시작 위치 저장
    if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
    {
        PlayerStartLocation = PlayerCharacter->GetActorLocation();
    }

    // HUD 위젯 생성
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UWBP_HUD>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void AMyGameMode::StartNewWave()
{
    // 플레이어를 시작 위치로 이동
    ResetPlayerPosition();
    
    // 플레이어 움직임 비활성화
    EnablePlayerMovement(false);
    
    // 1초 후에 웨이브 시작
    GetWorld()->GetTimerManager().SetTimer(
        PreWaveTimerHandle,
        this,
        &AMyGameMode::StartWaveAfterDelay,
        PreWaveDelay,
        false
    );

    // UI 업데이트
    UpdateWaveNumber(CurrentWave);
    
    // 웨이브 타이머 시작
    GetWorld()->GetTimerManager().SetTimer(
        WaveTimerHandle,
        this,
        &AMyGameMode::UpdateWaveTimer,
        1.0f,  // 1초마다 업데이트
        true   // 반복
    );
}

void AMyGameMode::StartWaveAfterDelay()
{
    // 플레이어 움직임 활성화
    EnablePlayerMovement(true);
    
    // SpawnVolume에게 웨이브 시작 알림
    TArray<AActor*> SpawnVolumes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), SpawnVolumes);
    
    for (AActor* Actor : SpawnVolumes)
    {
        if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(Actor))
        {
            SpawnVolume->StartWave();
        }
    }
}

void AMyGameMode::EndWave()
{
    // 웨이브 종료 시 처리
    // 다음 웨이브 시작 전에 StartNewWave가 호출됨
}

void AMyGameMode::ResetPlayerPosition()
{
    if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
    {
        PlayerCharacter->SetActorLocation(PlayerStartLocation);
        PlayerCharacter->GetController()->SetControlRotation(FRotator::ZeroRotator);
    }
}

void AMyGameMode::EnablePlayerMovement(bool bEnable)
{
    if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
    {
        PlayerCharacter->GetCharacterMovement()->SetMovementMode(
            bEnable ? MOVE_Walking : MOVE_None
        );
    }
}

void AMyGameMode::UpdateWaveTimer()
{
    static float RemainingTime = WaveDuration;
    
    if (RemainingTime > 0)
    {
        UpdateTimer(RemainingTime);
        RemainingTime -= 1.0f;
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
        RemainingTime = WaveDuration;  // 다음 웨이브를 위해 리셋
    }
}

// UI 업데이트 함수들 구현
void AMyGameMode::UpdateHealthBar(float HealthPercent)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateHealthBar(HealthPercent);
    }
}

void AMyGameMode::UpdateScore(int32 NewScore)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateScore(NewScore);
    }
}

void AMyGameMode::UpdateWaveNumber(int32 WaveNum)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateWaveNumber(WaveNum);
    }
}

void AMyGameMode::UpdateTimer(float RemainingTime)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateTimer(RemainingTime);
    }
}

