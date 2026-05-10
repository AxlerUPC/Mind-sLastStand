// Fill out your copyright notice in the Description page of Project Settings.

#include "MindLastStandCharacter.h"
#include "Enemigo.h"  // ← agregás este include arriba del todo junto a los otros


// Sets default values
AMindLastStandCharacter::AMindLastStandCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMindLastStandCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMindLastStandCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMindLastStandCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMindLastStandCharacter::Attack);
}


void AMindLastStandCharacter::Attack()
{
    if (bIsAttacking) return;  // bloquea si ya está atacando

    bIsAttacking = true;

    // Dispara el daño a los 0.5 segundos (ajustá según tu animación)
    GetWorldTimerManager().SetTimer(
        AttackTimerHandle,
        this,
        &AMindLastStandCharacter::ApplyAttackDamage,
        0.5f,  // ← cambiá este número a la mitad de tu animación
        false
    );
}

void AMindLastStandCharacter::ApplyAttackDamage()
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AEnemigo::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        AEnemigo* Enemigo = Cast<AEnemigo>(Actor);
        if (Enemigo)
        {
            Enemigo->TakeDamageFromPlayer();
            break;
        }
    }

    bIsAttacking = false;  // libera para el próximo ataque
}
