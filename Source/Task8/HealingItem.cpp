#include "HealingItem.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"

AHealingItem::AHealingItem()
{
	HealAmount = 10.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem_Implementation(AActor* Activator)
{
	if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
	{
		PlayerCharacter->AddHealth(HealAmount);
		DestroyItem();
	}
}
