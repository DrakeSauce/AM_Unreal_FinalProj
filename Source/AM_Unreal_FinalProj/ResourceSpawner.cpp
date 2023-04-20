// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceSpawner.h"

// Sets default values
AResourceSpawner::AResourceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourceSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

