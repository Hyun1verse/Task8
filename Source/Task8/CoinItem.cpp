#include "CoinItem.h"

ACoinItem::ACoinItem()
{
	PointValue = 10; // 기본 점수 10점
	ItemType = "Coin"; // 아이템 타입 설정
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, 
			FString::Printf(TEXT("Player gained %d points!"), PointValue));

		DestroyItem(); // 아이템 사라지기
	}
}
