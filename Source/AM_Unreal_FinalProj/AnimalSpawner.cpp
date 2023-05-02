// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalSpawner.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAnimalSpawner::AAnimalSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxSpawner = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));
}

// Called when the game starts or when spawned
void AAnimalSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(spawnTimer, this, &AAnimalSpawner::SpawnActor, spawnDelay, true);
}

// Called every frame
void AAnimalSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimalSpawner::SpawnActor()
{
	CheckActorsInArray();

	if (animalSpawn.Num() < maxActors)
	{
		int randomNum = FMath::RandRange(0, 10);

		//Set up the spawn
		FRotator randomRot;
		randomRot.Yaw = FMath::RandRange(1, 3) * 360.0f;
		randomRot.Pitch = FMath::RandRange(1, 3) * 360.0f;
		randomRot.Roll = FMath::RandRange(1, 3) * 360.0f;

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		//Spawn the actor in question
		if (!GetWorld()) { return; }

		AActor* timeObjSpawned = GetWorld()->SpawnActor<AActor>(actorToSpawn, GetRandomSpawnLoc(), randomRot, spawnParams);
		animalSpawn.Add(timeObjSpawned);
	}
}

void AAnimalSpawner::CheckActorsInArray()
{
	int validActors = 0;
	for (AActor* actor : animalSpawn) {
		if (!IsValid(actor))
			animalSpawn.Remove(actor);
			
	}
}

FVector AAnimalSpawner::GetRandomSpawnLoc()
{
	const FVector spawnOrigin = boxSpawner->Bounds.Origin;
	const FVector spawnLimits(boxSpawner->Bounds.BoxExtent.X, boxSpawner->Bounds.BoxExtent.Y, 0);

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnLimits);
}

