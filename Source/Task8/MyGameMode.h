#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameState.h"
#include "MyGameMode.generated.h"

USTRUCT(BlueprintType)
struct FWaveConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaveDuration = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumItemsToSpawn = 3;
};

UCLASS()
class TASK8_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();

	UFUNCTION(BlueprintCallable)
	void StartNewWave();

	UFUNCTION(BlueprintCallable)
	void EndWave();

	UFUNCTION(BlueprintCallable)
	void ResetPlayerPosition();

	void UpdateHealthBar(float HealthPercent);
	void UpdateScore(int32 NewScore);
	void UpdateWaveNumber(int32 WaveNum);
	void UpdateTimer(float InRemainingTime);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> GameOverWidgetClass;

	void GameOver();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UWBP_HUD* HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float PreWaveDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TArray<FWaveConfig> WaveConfigs;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 CurrentWave = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	FVector PlayerStartLocation;

private:
	void EnablePlayerMovement(bool bEnable);
	void StartWaveAfterDelay();
	void UpdateWaveTimer();

	FTimerHandle PreWaveTimerHandle;
	FTimerHandle WaveTimerHandle;
	float RemainingTime;
};
