// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharBase.h"
#include "Kismet/GameplayStatics.h"
#include "AThirdPersonCharBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharBase::AEnemyCharBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxHealth = 100;
}

// Called when the game starts or when spawned
void AEnemyCharBase::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
}

// Called every frame
void AEnemyCharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (health <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroying Actor!"));
		AThirdPersonCharBase* playerRef = Cast<AThirdPersonCharBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		playerRef->food++;
		playerRef->UpdateUI();
		Destroy();
	}

}

// Called to bind functionality to input
void AEnemyCharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharBase::EnemyTakeDamage(float damageToTake)
{
	PlayAnimMontage(hitAnim, 1, NAME_None);

	health -= damageToTake;
}
