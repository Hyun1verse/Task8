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
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, 
				FString::Printf(TEXT("체력 회복: %.1f"), HealAmount));
		}
		
		DestroyItem();
	}
}
