// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceGenerator.h"
#include "AThirdPersonCharBase.h"

// Sets default values
AResourceGenerator::AResourceGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourceGenerator::BeginPlay()
{
	Super::BeginPlay();
	playerRef = Cast<AThirdPersonCharBase>(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetTimerManager().SetTimer(genTimer, this, &AResourceGenerator::GenerateResource, generateTime, true);
}

void AResourceGenerator::GenerateResource()
{
}

// Called every frame
void AResourceGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

