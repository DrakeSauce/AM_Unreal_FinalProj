// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ResourceNode.h"
#include "ResourceSpawner.generated.h"

UCLASS()
class AM_UNREAL_FINALPROJ_API AResourceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceSpawner();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* boxSpawner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AResourceNode> actorToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<AActor*> spawnedObj;
	UPROPERTY()
		FTimerHandle spawnTimer;
	UPROPERTY()
		float spawnDelay;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void SpawnActor();
	UFUNCTION()
		FVector GetRandomSpawnLoc();


};
