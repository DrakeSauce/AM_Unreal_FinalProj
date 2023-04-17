// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceNode.generated.h"

UENUM(BlueprintType)
enum class ResourceType : uint8 {
	WOOD,
	STONE,
	IRON
};


class UGeometryCollectionComponent;
UCLASS()
class AM_UNREAL_FINALPROJ_API AResourceNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceNode();

	UFUNCTION(BlueprintCallable, Category="Behaviour")
		void DamageHealth(float damage);
	UFUNCTION()
		bool bCheckIsDead();
	UFUNCTION(BlueprintImplementableEvent)
		void PhysEvent();
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeEvent();
	UFUNCTION(BlueprintCallable)
		void InitializeResource(ResourceType type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behaviour")
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Behaviour")
		float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behaviour")
		float damageResist;

	UPROPERTY(EditAnywhere, Category = "Resource")
		float wood;
	UPROPERTY(VisibleAnywhere, Category = "Resource")
		float stone;
	UPROPERTY(VisibleAnywhere, Category = "Resource")
		float iron;

	UPROPERTY(EditAnywhere, Category = "Behaviour")
		ResourceType resourceType;
};

