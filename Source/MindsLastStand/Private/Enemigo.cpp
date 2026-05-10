
#include "Enemigo.h"
#include "EnemyAIController.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "AIController.h"
#include "TimerManager.h"

AEnemigo::AEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;

    HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
    HitSphere->SetSphereRadius(150.f);
    HitSphere->SetupAttachment(RootComponent);

    // Asigna el AIController
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    AIControllerClass = AEnemyAIController::StaticClass();
}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();

    if (PatrolPoints.Num() > 0)
    {
        MoveToNextPoint();
    }
}

void AEnemigo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEnemigo::MoveToNextPoint()
{
    if (PatrolPoints.Num() == 0) return;

    AActor* TargetPoint = PatrolPoints[CurrentPatrolIndex];
    if (!TargetPoint) return;

    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        AIController->MoveToActor(TargetPoint, 50.f);

        // Cuando llega, espera 1 segundo y va al siguiente punto
        GetWorldTimerManager().SetTimer(
            PatrolTimerHandle,
            [this]()
            {
                // Lógica A → B → A
                if (bMovingForward)
                {
                    CurrentPatrolIndex++;
                    if (CurrentPatrolIndex >= PatrolPoints.Num())
                    {
                        CurrentPatrolIndex = PatrolPoints.Num() - 2;
                        bMovingForward = false;
                    }
                }
                else
                {
                    CurrentPatrolIndex--;
                    if (CurrentPatrolIndex < 0)
                    {
                        CurrentPatrolIndex = 1;
                        bMovingForward = true;
                    }
                }
                MoveToNextPoint();
            },
            2.0f,
            false
        );
    }
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