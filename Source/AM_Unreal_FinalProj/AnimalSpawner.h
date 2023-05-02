// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemyCharBase.h"
#include "AnimalSpawner.generated.h"

UCLASS()
class AM_UNREAL_FINALPROJ_API AAnimalSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* boxSpawner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AEnemyCharBase> actorToSpawn;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> animalSpawn;
	UPROPERTY()
		FTimerHandle spawnTimer;
	UPROPERTY(EditAnywhere)
		float spawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int maxActors;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void SpawnActor();
	UFUNCTION()
		void CheckActorsInArray();
	UFUNCTION()
		FVector GetRandomSpawnLoc();

};
