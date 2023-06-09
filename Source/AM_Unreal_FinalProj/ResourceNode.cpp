// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceNode.h"


// Sets default values
AResourceNode::AResourceNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	maxHealth = 100.0f;
	health = 100.0f;
}


// Called when the game starts or when spawned
void AResourceNode::BeginPlay()
{
	Super::BeginPlay();
	InitializeResource(resourceType);
}

// Called every frame
void AResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceNode::DamageHealth(float damage)
{
	float damageTotal = (damage - damageResist);

	if (damageTotal < 0)
		damageTotal = 0;
	else 
		health -= damageTotal;

	if (bCheckIsDead())
	{
		PhysEvent();
	}
}

bool AResourceNode::bCheckIsDead()
{
	if (health <= 0) { return true; }
	else {return false; }
}

void AResourceNode::InitializeResource(ResourceType type)
{
	float scaleSize;
	FVector scale;

	switch (type) {
		case ResourceType::WOOD:
				damageResist = FMath::RandRange(0, 5);
				wood = FMath::RandRange(100, 300);
				maxHealth = wood;
				health = maxHealth;

				scaleSize = wood / 300;

				scale.Set(scaleSize, scaleSize, scaleSize);
				SetActorScale3D(scale);

				InitializeEvent();
			break;
		case ResourceType::STONE:
				damageResist = FMath::RandRange(5, 10);
				stone = FMath::RandRange(50, 150);
				maxHealth = stone;
				health = maxHealth;

				scaleSize = stone / 150;
				rockScale = scaleSize;

				scale.Set(scaleSize, scaleSize, scaleSize);
				SetActorScale3D(scale);

				InitializeEvent();
			break;
		case ResourceType::IRON:
				damageResist = FMath::RandRange(10, 20);
				iron = FMath::RandRange(25, 50);
				maxHealth = iron * 2;
				health = maxHealth;

				scaleSize = iron / 50;
				
				scale.Set(scaleSize, scaleSize, scaleSize);
				SetActorScale3D(scale);

				InitializeEvent();
			break;
	}
}

