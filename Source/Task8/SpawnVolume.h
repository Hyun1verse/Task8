#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class ABaseItem;
class AMyGameMode;

UCLASS()
class TASK8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	void StartWave();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<TSubclassOf<class ABaseItem>> ItemsToSpawn;

	UPROPERTY(EditAnywhere, Category = "Wave")
	int32 CurrentWave;

	UPROPERTY(EditAnywhere, Category = "Wave")
	float WaveDuration;

	UPROPERTY(EditAnywhere, Category = "Wave")
	float TimeBetweenWaves;

	UPROPERTY(EditAnywhere, Category = "Wave")
	TArray<int32> ItemsPerWave;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* SpawnArea;

private:
	FTimerHandle WaveTimerHandle;
	FTimerHandle SpawnTimerHandle;
	float CurrentWaveTime;
	
	void EndWave();
	void SpawnItem();
	FVector GetRandomPointInVolume();
};
