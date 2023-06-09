// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharBase.h"
#include "Kismet/GameplayStatics.h"
#include "ResourceGenerator.h"
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
	bIsDead = false;
}

// Called every frame
void AEnemyCharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void AEnemyCharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharBase::EnemyTakeDamage(float damageToTake)
{
	health -= damageToTake;
	if (!bIsDead)
		PlayAnimMontage(hitAnim, 1, NAME_None);

	if (health <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroying Actor!"));
		AThirdPersonCharBase* playerRef = Cast<AThirdPersonCharBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!bIsDead)
			playerRef->food++;
		playerRef->UpdateUI();
		bIsDead = true;
	}
}

void AEnemyCharBase::AttackStructure()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	TArray<AActor*> outHit;

	if (UKismetSystemLibrary::SphereOverlapActors(
		GetController(),
		GetActorLocation(),
		500,
		objectTypes,
		nullptr,
		actorsToIgnore,
		outHit
	))
	{
		for (AActor* hitObj : outHit)
		{
			if (IsValid(hitObj))
			{
				if (AResourceGenerator* enemy = Cast<AResourceGenerator>(hitObj))
				{
					if (!IsValid(enemy)) { return; }
				
					PlayAnimMontage(attackAnim, 1.0f, NAME_None);
					enemy->StructTakeDamage(damage);
				}
			}
		}
	}
}
