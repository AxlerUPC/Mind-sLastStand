#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class MINDSLASTSTAND_API AEnemigo : public AActor
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

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* HitSphere;

    void Die();
};