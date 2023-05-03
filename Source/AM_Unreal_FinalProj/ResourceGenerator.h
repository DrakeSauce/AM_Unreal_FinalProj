// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AThirdPersonCharBase.h"
#include "ResourceGenerator.generated.h"

UENUM(BlueprintType)
enum class ResourceGenType : uint8 {
	WOOD,
	STONE,
	IRON
};

UCLASS()
class AM_UNREAL_FINALPROJ_API AResourceGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceGenerator();
	UFUNCTION()
		void GenerateResource();
	UFUNCTION()
		void HealStructure();
	UFUNCTION()
		void StructTakeDamage(float damageToTake);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateGenUI();
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeGenUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float generateTime;

	UPROPERTY(VisibleAnywhere)
		float woodGen;
	UPROPERTY(VisibleAnywhere)
		float stoneGen;
	UPROPERTY(VisibleAnywhere)
		float ironGen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxHealth;

	UPROPERTY(VisibleAnywhere)
		FTimerHandle genTimer;

	UPROPERTY(EditAnywhere)
		ResourceGenType genType;

	AThirdPersonCharBase* playerRef;
};
