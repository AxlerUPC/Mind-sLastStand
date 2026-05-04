#include "Enemigo.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

AEnemigo::AEnemigo()
{
    HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
    HitSphere->SetSphereRadius(150.f);
    SetRootComponent(HitSphere);
}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Enemigo listo: %s"), *GetName());
}

void AEnemigo::TakeDamageFromPlayer()
{
    Health -= DamagePerHit;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
            FString::Printf(TEXT("%s recibio danio. Vida: %.0f"), *GetName(), Health));
    }

    if (Health <= 0.f)
    {
        Die();
    }
}

void AEnemigo::Die()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
            FString::Printf(TEXT("%s murio!"), *GetName()));
    }

    Destroy();
}