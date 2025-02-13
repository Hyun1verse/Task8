#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

UCLASS()
class TASK8_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyGameState();

	// 웨이브 관련
	UPROPERTY(ReplicatedUsing = OnRep_CurrentWave)
	int32 CurrentWave;

	UFUNCTION()
	void OnRep_CurrentWave();

	// 점수 관련
	UPROPERTY(ReplicatedUsing = OnRep_Score)
	int32 Score;

	UFUNCTION()
	void OnRep_Score();

	// 타이머 관련
	UPROPERTY(Replicated)
	float RemainingTime;

	void AddScore(int32 Points);
	void SetCurrentWave(int32 NewWave);
	void SetRemainingTime(float NewTime);
	
	UFUNCTION(BlueprintPure)
	float GetRemainingTime() const { return RemainingTime; }

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWave() const { return CurrentWave; }

	UFUNCTION(BlueprintPure)
	int32 GetScore() const { return Score; }
};
