#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

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

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UWBP_HUD* HUDWidget;

	void UpdateHealthBar(float HealthPercent);
	void UpdateScore(int32 NewScore);
	void UpdateWaveNumber(int32 WaveNum);
	void UpdateTimer(float RemainingTime);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	FVector PlayerStartLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float PreWaveDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float WaveDuration;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 CurrentWave;

private:
	void EnablePlayerMovement(bool bEnable);
	void StartWaveAfterDelay();
	void UpdateWaveTimer();

	FTimerHandle PreWaveTimerHandle;
	FTimerHandle WaveTimerHandle;
};
