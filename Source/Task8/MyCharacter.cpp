#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyGameMode.h"

AMyCharacter::AMyCharacter()
{
    // 기본값 설정
    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
    Score = 0;

    Tags.Add(FName("Player"));

    // 카메라 회전 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 캐릭터 무브먼트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // 카메라 붐 생성
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;

    // Enhanced Input 설정
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    // 초기 체력 UI 업데이트 추가
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateHealthBar(GetHealthPercentage());
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // 일시정지 입력 추가
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMyCharacter::PauseGame);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // 전후 이동
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(ForwardDirection, MovementVector.Y);

        // 좌우 이동
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    CurrentHealth -= ActualDamage;
    
    // GameMode에 체력 업데이트 알림
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateHealthBar(GetHealthPercentage());
        
        // 체력이 0 이하면 게임 오버
        if (CurrentHealth <= 0)
        {
            GameMode->GameOver();
        }
    }
    
    return ActualDamage;
}

void AMyCharacter::AddScore(int32 Points)
{
    if (AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>())
    {
        GameState->AddScore(Points);  // GameState를 통해 점수 업데이트
    }
}

void AMyCharacter::AddHealth(float HealAmount)
{
    // 현재 체력이 최대 체력보다 작을 때만 메시지 표시
    bool bCanHeal = CurrentHealth < MaxHealth;
    
    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Min(CurrentHealth + HealAmount, MaxHealth);
    
    if (GEngine && bCanHeal)  // 체력이 최대가 아닐 때만 메시지 표시
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, 
            FString::Printf(TEXT("체력 회복: %.1f"), HealAmount));
    }
    
    // UI 업데이트
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->UpdateHealthBar(GetHealthPercentage());
    }
}

float AMyCharacter::GetHealthPercentage() const
{
    return CurrentHealth / MaxHealth;
}

void AMyCharacter::PauseGame()
{
    if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->PauseGame();
    }
} 