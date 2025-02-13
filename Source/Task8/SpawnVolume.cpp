#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "BaseItem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "MyGameMode.h"
#include "MyGameState.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;
    
    // 기본값 설정
    CurrentWave = 0;
    WaveDuration = 30.0f;
    TimeBetweenWaves = 5.0f;
    
    // 기본 스폰 개수 설정
    NumItemsToSpawn = 3;
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
    // 첫 번째 웨이브 시작
    StartWave();
}

void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnVolume::StartWave()
{
    // 설정된 개수만큼 아이템 스폰
    for (int32 i = 0; i < NumItemsToSpawn; i++)
    {
        SpawnItem();
    }

    if (AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>())
    {
        GameState->SetCurrentWave(CurrentWave);
    }
}

void ASpawnVolume::EndWave()
{
    if (CurrentWave < 3)  // 3웨이브까지
    {
        CurrentWave++;
        
        // GameState 업데이트
        if (AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>())
        {
            GameState->SetCurrentWave(CurrentWave);
        }
        
        if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
        {
            FTimerHandle NextWaveTimer;
            GetWorldTimerManager().SetTimer(NextWaveTimer, [GameMode]()
            {
                GameMode->StartNewWave();
            }, TimeBetweenWaves, false);
        }
    }
    else  // 마지막 웨이브 종료 시 게임 오버 호출
    {
        if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->GameOver();
        }
    }
}

void ASpawnVolume::SpawnItem()
{
    if (ItemsToSpawn.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, ItemsToSpawn.Num() - 1);
        FVector SpawnLocation = GetRandomPointInVolume();
        FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
        
        GetWorld()->SpawnActor<ABaseItem>(ItemsToSpawn[RandomIndex], SpawnLocation, SpawnRotation);
    }
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector SpawnOrigin = SpawnArea->Bounds.Origin;
    FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;
    
    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}
