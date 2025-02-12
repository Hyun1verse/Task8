#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "BaseItem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "MyGameMode.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;
    
    // 기본값 설정
    CurrentWave = 0;
    WaveDuration = 30.0f;
    TimeBetweenWaves = 5.0f;
    
    // 각 웨이브별 스폰할 아이템 개수 설정
    ItemsPerWave.Add(3);  // Wave 1
    ItemsPerWave.Add(5);  // Wave 2
    ItemsPerWave.Add(7);  // Wave 3
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
    CurrentWave++;
    
    if (CurrentWave <= ItemsPerWave.Num())
    {
        FString WaveMessage = FString::Printf(TEXT("Wave %d 시작!"), CurrentWave);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, WaveMessage);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *WaveMessage);

        // 현재 웨이브에 해당하는 수만큼 아이템을 한번에 스폰
        for (int32 i = 0; i < ItemsPerWave[CurrentWave - 1]; i++)
        {
            SpawnItem();
        }
        
        // 웨이브 종료 타이머 설정
        GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpawnVolume::EndWave, WaveDuration, false);
    }
    else
    {
        // 모든 웨이브 완료
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("모든 웨이브 완료!"));
        UE_LOG(LogTemp, Warning, TEXT("모든 웨이브 완료!"));
    }
}

void ASpawnVolume::EndWave()
{
    if (CurrentWave < ItemsPerWave.Num())
    {
        // GameMode에 웨이브 종료 알림
        if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->EndWave();
            
            // 다음 웨이브 시작
            FTimerHandle NextWaveTimer;
            GetWorldTimerManager().SetTimer(NextWaveTimer, [GameMode]()
            {
                GameMode->StartNewWave();
            }, TimeBetweenWaves, false);
        }
        
        FString Message = FString::Printf(TEXT("Wave %d 종료! %d초 후 다음 웨이브 시작"), 
            CurrentWave, FMath::RoundToInt(TimeBetweenWaves));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, Message);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
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

