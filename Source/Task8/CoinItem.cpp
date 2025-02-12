#include "CoinItem.h"

ACoinItem::ACoinItem()
{
	PointValue = 10;
	ItemType = "Coin";
}

void ACoinItem::ActivateItem_Implementation(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Player gained %d points!"), PointValue));
		}
        
		UE_LOG(LogTemp, Warning, TEXT("플레이어가 코인을 획득했습니다. 점수: %d"), PointValue);
        
		DestroyItem();
	}
}
