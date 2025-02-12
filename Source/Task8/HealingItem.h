#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class TASK8_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AHealingItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing")
	int32 HealAmount;

	// 아이템 활성화 (획득 시 실행되는 함수)
	virtual void ActivateItem(AActor* Activator) override;
};
