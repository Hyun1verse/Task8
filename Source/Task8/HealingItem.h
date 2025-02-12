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
	float HealAmount;
	
	virtual void ActivateItem_Implementation(AActor* Activator);
};
