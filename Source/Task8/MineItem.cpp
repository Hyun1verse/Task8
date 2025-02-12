#include "MineItem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

AMineItem::AMineItem()
{
	ExplosionDamage = 20.0f;
	ExplosionRadius = 200.0f;
	ExplosionDelay = 1.5f;  // 1.5초 후 폭발
	ItemType = "Mine";

	// 기본 폭발 이펙트 로드
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}
}

void AMineItem::ActivateItem_Implementation(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		// 경고 메시지 표시
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("지뢰가 활성화되었습니다!"));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("지뢰가 활성화되었습니다. %.1f초 후 폭발합니다."), ExplosionDelay);

		// 폭발 타이머 설정
		GetWorld()->GetTimerManager().SetTimer(
			ExplosionTimerHandle,
			this,
			&AMineItem::StartExplosion,
			ExplosionDelay,
			false
		);
	}
}

void AMineItem::StartExplosion()
{
	// 폭발 이펙트 재생
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f)
		);
	}

	// 범위 내 데미지 적용
	ApplyExplosionDamage();

	// 화면에 메시지 표시
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("지뢰 폭발!"));
	}

	UE_LOG(LogTemp, Warning, TEXT("지뢰가 폭발했습니다!"));
	DestroyItem();
}

void AMineItem::ApplyExplosionDamage()
{
	// 폭발 범위 내의 모든 플레이어 검출
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), Players);

	for (AActor* Player : Players)
	{
		float Distance = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
		if (Distance <= ExplosionRadius)
		{
			ApplyDamage(Player);
		}
	}
}

void AMineItem::ApplyDamage(AActor* DamagedActor)
{
	if (DamagedActor)
	{
		UGameplayStatics::ApplyDamage(
			DamagedActor,
			ExplosionDamage,
			nullptr,
			this,
			nullptr
		);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, 
				FString::Printf(TEXT("지뢰 데미지 적용: %.1f"), ExplosionDamage));
		}
		UE_LOG(LogTemp, Warning, TEXT("지뢰 데미지 적용: %f"), ExplosionDamage);
	}
}
