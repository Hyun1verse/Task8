#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AMineItem::AMineItem()
{
	// 기본 값 설정
	ExplosionDelay = 5.0f;      // 5초 후 폭발
	ExplosionDamage = 30.0f;    // 폭발 데미지
	ItemType = "Mine";          // 아이템 타입 설정

	// 폭발 범위 콜리전 추가
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(300.0f);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
}

void AMineItem::BeginPlay()
{
	Super::BeginPlay();
}

void AMineItem::ActivateItem(AActor* Activator)
{
	// 플레이어가 밟으면 폭발 카운트다운 시작
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay);
}

void AMineItem::Explode()
{
	// 폭발 범위 안의 액터 가져오기
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("💥 지뢰 폭발! 플레이어 피해!"));
		}
	}

	// 폭발 이펙트 재생
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}

	// 지뢰 제거
	DestroyItem();
}
