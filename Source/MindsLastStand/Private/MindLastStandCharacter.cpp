// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"  // ← agregás este include arriba del todo junto a los otros
#include "MindLastStandCharacter.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Attack llamado"));

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, AEnemigo::StaticClass());

	UE_LOG(LogTemp, Warning, TEXT("Dummies cerca: %d"), OverlappingActors.Num());

	for (AActor* Actor : OverlappingActors)
	{
		AEnemigo* Enemigo = Cast<AEnemigo>(Actor);
		if (Enemigo)
		{
			Enemigo->TakeDamageFromPlayer();
			break;
		}
	}
}
