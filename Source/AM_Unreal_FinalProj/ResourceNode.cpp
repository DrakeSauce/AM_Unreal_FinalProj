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

	//if (damageTotal > 0)
	health -= damageTotal;

	if (bCheckIsDead())
	{
		PhysEvent();
		//this->Destroy();
	}
}

bool AResourceNode::bCheckIsDead()
{
	if (health <= 0) { return true; }
	else {return false; }
}

void AResourceNode::InitializeResource(ResourceType type)
{
	switch (type) {
		case ResourceType::WOOD:
				damageResist = FMath::RandRange(0, 5);
				maxHealth = FMath::RandRange(100, 300);
				wood = maxHealth;
				health = maxHealth;
				InitializeEvent();
			break;
		case ResourceType::STONE:
				damageResist = FMath::RandRange(5, 10);
				maxHealth = FMath::RandRange(50, 150);
				stone = maxHealth;
				health = maxHealth;
				InitializeEvent();
			break;
		case ResourceType::IRON:
				damageResist = FMath::RandRange(10, 15);
				maxHealth = FMath::RandRange(25, 50);
				iron = maxHealth;
				health = maxHealth;
				InitializeEvent();
			break;
	}
}

