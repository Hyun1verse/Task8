#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class TASK8_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    virtual void BeginPlay() override;

    // Enhanced Input 관련 변수들
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* PauseAction;

    // 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    // Enhanced Input 함수들
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    // 데미지 처리를 위한 함수
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
        class AController* EventInstigator, AActor* DamageCauser) override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 점수 관련
    UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
    int32 Score;

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void AddScore(int32 Points);

    // 체력 관련
    UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
    float MaxHealth;

    UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
    float CurrentHealth;

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void AddHealth(float HealAmount);

    UFUNCTION(BlueprintPure, Category = "Gameplay")
    float GetHealthPercentage() const;

    // 일시정지 함수 추가
    void PauseGame();
}; 