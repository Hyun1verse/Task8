#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

ABaseItem::ABaseItem()
{
    PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->SetupAttachment(Scene);
    Collision->InitSphereRadius(100.0f);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

    // 🔥 이벤트 바인딩 수정
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnOverlapEnd);
}

void ABaseItem::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 새로운 함수 추가
void ABaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    OnItemOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ABaseItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    OnItemEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

// 아이템과 충돌한 액터 정보 출력
void ABaseItem::OnItemOverlap_Implementation(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("🔵 아이템 충돌 감지: %s"), *OtherActor->GetName());

        if (OtherActor->ActorHasTag(TEXT("Player")))
        {
            UE_LOG(LogTemp, Warning, TEXT("🟢 플레이어가 아이템과 충돌! 아이템 활성화 실행"));
            ActivateItem_Implementation(OtherActor);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("🟡 충돌한 객체는 플레이어가 아님"));
        }
    }
}

// 아이템과 충돌이 끝났을 때 메시지 출력
void ABaseItem::OnItemEndOverlap_Implementation(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("⚪ 아이템과 충돌이 끝남: %s"), *OtherActor->GetName());
    }
}

// 아이템이 활성화될 때 출력
void ABaseItem::ActivateItem_Implementation(AActor* Activator)
{
    UE_LOG(LogTemp, Warning, TEXT("💥 아이템 활성화됨!"));
    DestroyItem();
}

// 아이템이 파괴될 때 출력
void ABaseItem::DestroyItem()
{
    UE_LOG(LogTemp, Warning, TEXT("🗑️ 아이템이 제거됨!"));
    Destroy();
}
