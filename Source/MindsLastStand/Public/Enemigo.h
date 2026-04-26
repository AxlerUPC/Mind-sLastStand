// Fill out your copyright notice in the Description page of Project Settings.

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

    // Vida actual
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.f;

    // Daño que recibe por golpe
    UPROPERTY(EditAnywhere)
    float DamagePerHit = 25.f;

    // Llamada cuando recibe daño
    void TakeDamageFromPlayer();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* HitSphere;

    void Die();
};