#include "HealingItem.h"
#include "GameFramework/Character.h"

AHealingItem::AHealingItem()
{
	HealAmount = 10;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	// 플레이어가 아이템을 먹었는지 확인
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue,
			FString::Printf(TEXT("Player healed by %d HP!"), HealAmount));

		// 여기에 실제로 체력 회복 기능을 추가할 수 있음 (예: 플레이어 캐릭터의 HP 증가)

		DestroyItem(); // 아이템 사라지기
	}
}
