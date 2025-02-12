#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

class UParticleSystem;

UCLASS()
class TASK8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();

protected:
	UPROPERTY(EditAnywhere, Category = "Mine")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = "Mine")
	float ExplosionDamage;
	
	UPROPERTY(EditAnywhere, Category = "Mine")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, Category = "Mine")
	float ExplosionDelay;

	virtual void ActivateItem_Implementation(AActor* Activator) override;

private:
	FTimerHandle ExplosionTimerHandle;
	void ApplyDamage(AActor* DamagedActor);
	void ApplyExplosionDamage();
	void StartExplosion();
};
