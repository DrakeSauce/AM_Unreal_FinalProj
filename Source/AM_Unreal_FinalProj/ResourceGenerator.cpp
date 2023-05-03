// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "AThirdPersonCharBase.h"

// Sets default values
AResourceGenerator::AResourceGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	genType = ResourceGenType::WOOD;
}

// Called when the game starts or when spawned
void AResourceGenerator::BeginPlay()
{
	Super::BeginPlay();

	switch (genType) {
		case ResourceGenType::WOOD:
			woodGen = 50;

			stoneGen = 0;
			ironGen = 0;
			break;
		case ResourceGenType::STONE:
			stoneGen = 25;

			woodGen = 0;
			ironGen = 0;
			break;
		case ResourceGenType::IRON:
			ironGen = 10;

			stoneGen = 0;
			woodGen = 0;
			break;
	}

	InitializeGenUI();
	playerRef = Cast<AThirdPersonCharBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetWorld()->GetTimerManager().SetTimer(genTimer, this, &AResourceGenerator::GenerateResource, generateTime, true);
}

void AResourceGenerator::GenerateResource()
{
	//playerRef = Cast<AThirdPersonCharBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(playerRef)) {
		switch (genType) {
		case ResourceGenType::WOOD:
			playerRef->wood += woodGen;
			HealStructure();
			break;
		case ResourceGenType::STONE:
			playerRef->stone += stoneGen;
			HealStructure();
			break;
		case ResourceGenType::IRON:
			playerRef->iron += ironGen;
			HealStructure();
			break;
		}
		UpdateGenUI();
		playerRef->UpdateUI();
	}
	else {
		UE_LOG( LogTemp, Warning, TEXT("Error No Reference Found For Player") );
	}
}

void AResourceGenerator::HealStructure()
{
	if (health < maxHealth)
		health += 10;
	else if (health > maxHealth)
		health = maxHealth;
}

void AResourceGenerator::StructTakeDamage(float damageToTake)
{
	health -= damageToTake;

	if (health <= 0) {
		Destroy();
	}

	UpdateGenUI();
}



// Called every frame
void AResourceGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

