#include "CoinItem.h"
#include "MyCharacter.h"

ACoinItem::ACoinItem()
{
	PointValue = 10;
	ItemType = "Coin";
}

void ACoinItem::ActivateItem_Implementation(AActor* Activator)
{
	if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
	{
		PlayerCharacter->AddScore(PointValue);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, 
				FString::Printf(TEXT("점수 획득: %d점!"), PointValue));
		}
		
		DestroyItem();
	}
}
