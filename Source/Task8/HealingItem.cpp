#include "HealingItem.h"
#include "GameFramework/Character.h"

AHealingItem::AHealingItem()
{
	HealAmount = 10;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem_Implementation(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue,
			FString::Printf(TEXT("Player healed by %d HP!"), HealAmount));

		DestroyItem();
	}
}
