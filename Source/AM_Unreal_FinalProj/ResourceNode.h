// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Field/FieldSystemObjects.h"
#include "Field/FieldSystemActor.h"
#include "ResourceNode.generated.h"

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
		bool bCheckIsDead(float healthRemaining);
	UFUNCTION(BlueprintImplementableEvent)
		void PhysEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Behaviour")
		float health;
	UPROPERTY(EditAnywhere, Category="Behaviour")
		float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Behaviour")
		UGeometryCollectionComponent* destroyable;
};
