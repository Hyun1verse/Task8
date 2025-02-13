#include "MyGameMode.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Blueprint/UserWidget.h"
#include "WBP_HUD.h"
#include "MyGameState.h"
#include "WBP_GameOver.h"

AMyGameMode::AMyGameMode()
{
    PreWaveDelay = 1.0f;  // 1초 대기
    CurrentWave = 0;

    // 기본 웨이브 설정 추가
    FWaveConfig DefaultConfig;
    DefaultConfig.WaveDuration = 30.0f;
    DefaultConfig.NumItemsToSpawn = 3;
    WaveConfigs.Add(DefaultConfig);

    RemainingTime = DefaultConfig.WaveDuration;
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

            StartNewWave();
        }
    }
}

void AMyGameMode::StartNewWave()
{
    CurrentWave++;
    
    // 웨이브 설정 가져오기
    FWaveConfig CurrentConfig;
    if (WaveConfigs.IsValidIndex(CurrentWave - 1))
    {
        CurrentConfig = WaveConfigs[CurrentWave - 1];
    }
    else
    {
        // 기본값 사용
        CurrentConfig.WaveDuration = 30.0f;
        CurrentConfig.NumItemsToSpawn = 3;
    }
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, 
            FString::Printf(TEXT("Wave %d Start!"), CurrentWave));
    }
    
    if (AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>())
    {
        RemainingTime = CurrentConfig.WaveDuration;
        MyGameState->WaveDuration = CurrentConfig.WaveDuration;  // GameState에도 설정
        MyGameState->SetCurrentWave(CurrentWave);
    }

    // SpawnVolume에 아이템 스폰 개수 전달
    TArray<AActor*> SpawnVolumes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), SpawnVolumes);
    for (AActor* Actor : SpawnVolumes)
    {
        if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(Actor))
        {
            SpawnVolume->SetNumItemsToSpawn(CurrentConfig.NumItemsToSpawn);
        }
    }
    
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
    UpdateTimer(RemainingTime);
    
    // 웨이브 타이머 시작
    GetWorld()->GetTimerManager().SetTimer(
        WaveTimerHandle,
        this,
        &AMyGameMode::UpdateWaveTimer,
        1.0f,
        true
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
    if (CurrentWave < 3)  // 3웨이브까지
    {
        StartNewWave();
    }
    else
    {
        GameOver();  // 게임 오버 호출
    }
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
    if (RemainingTime > 0)
    {
        if (AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>())
        {
            MyGameState->SetRemainingTime(RemainingTime);
            UpdateTimer(RemainingTime);  // UI 업데이트
            UpdateWaveNumber(CurrentWave);  // 웨이브 번호 UI 업데이트 추가
        }
        RemainingTime -= 1.0f;
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
        EndWave();
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

void AMyGameMode::UpdateTimer(float InRemainingTime)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateTimer(InRemainingTime);
    }
}

void AMyGameMode::GameOver()
{
    // 타이머 정지 추가
    GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);

    // 플레이어 입력 비활성화
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->DisableInput(PC);
        PC->SetShowMouseCursor(true);
        PC->SetInputMode(FInputModeUIOnly());
    }

    // 게임오버 UI 표시
    if (GameOverWidgetClass)
    {
        if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass))
        {
            if (UWBP_GameOver* GameOverWidget = Cast<UWBP_GameOver>(Widget))
            {
                if (AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>())
                {
                    GameOverWidget->DisplayFinalScore(MyGameState->GetScore());
                }
                GameOverWidget->AddToViewport();
            }
        }
    }
}

void AMyGameMode::PauseGame()
{
    // 게임 일시정지
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->SetPause(true);
        
        // 마우스 커서 표시
        PC->SetShowMouseCursor(true);
        PC->SetInputMode(FInputModeUIOnly());

        // 일시정지 메뉴 표시
        if (PauseMenuWidgetClass)
        {
            if (UUserWidget* PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass))
            {
                PauseWidget->AddToViewport();
            }
        }
    }
}
