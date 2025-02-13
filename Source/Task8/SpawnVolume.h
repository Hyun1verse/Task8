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
	void EndWave();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnArea;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TArray<int32> ItemsPerWave;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float TimeBetweenWaves = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<TSubclassOf<class ABaseItem>> ItemsToSpawn;

private:
	void SpawnItem();
	FVector GetRandomPointInVolume();
	
	int32 CurrentWave = 0;
	float WaveDuration = 30.0f;
	FTimerHandle SpawnTimerHandle;
};
