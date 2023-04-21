// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceSpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AResourceSpawner::AResourceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxSpawner = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));
}

// Called when the game starts or when spawned
void AResourceSpawner::BeginPlay()
{
	Super::BeginPlay();
	spawnedObj.SetNum(5);
	spawnDelay = FMath::RandRange(0, 5);

	GetWorld()->GetTimerManager().SetTimer(spawnTimer, this, &AResourceSpawner::SpawnActor, spawnDelay, true);
}

// Called every frame
void AResourceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceSpawner::SpawnActor()
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

	//actorToSpawn->
	AActor* timeObjSpawned = GetWorld()->SpawnActor<AActor>(actorToSpawn, GetRandomSpawnLoc(), randomRot, spawnParams);
	spawnedObj.Add(timeObjSpawned);
}

FVector AResourceSpawner::GetRandomSpawnLoc()
{
	const FVector spawnOrigin = boxSpawner->Bounds.Origin;
	const FVector spawnLimits = boxSpawner->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnLimits);
}

