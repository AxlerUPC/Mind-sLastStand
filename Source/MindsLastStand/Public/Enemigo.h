#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

UCLASS()
class MINDSLASTSTAND_API AEnemigo : public ACharacter  // ← cambiás AActor por ACharacter
{
    GENERATED_BODY()

public:
    AEnemigo();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.f;

    UPROPERTY(EditAnywhere)
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere)
    float DamagePerHit = 25.f;

    UFUNCTION(BlueprintCallable)
    void TakeDamageFromPlayer();

    // Puntos de patrulla — los asignás desde el editor
    UPROPERTY(EditAnywhere)
    TArray<AActor*> PatrolPoints;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* HitSphere;

    void Die();
    void MoveToNextPoint();

    int32 CurrentPatrolIndex = 0;
    bool bMovingForward = true;
    FTimerHandle PatrolTimerHandle;
};