#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

class USphereComponent;
class UParticleSystem;

UCLASS()
class TASK8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();
	void BeginPlay();

protected:
	virtual void ActivateItem(AActor* Activator) override;

private:
	// 폭발 범위 감지용 SphereComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mine|Component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* ExplosionCollision;

	// 폭발 효과 (파티클)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine|Effect", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ExplosionEffect;

	// 폭발 대기 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine|Settings", meta = (AllowPrivateAccess = "true"))
	float ExplosionDelay;

	// 폭발 범위 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine|Settings", meta = (AllowPrivateAccess = "true"))
	float ExplosionRadius;

	// 폭발 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine|Settings", meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	// 폭발 타이머 핸들
	FTimerHandle ExplosionTimerHandle;

	// 폭발 실행 함수
	void Explode();
};
