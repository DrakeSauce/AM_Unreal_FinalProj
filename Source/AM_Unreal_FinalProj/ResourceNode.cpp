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
	health = maxHealth;
}

// Called every frame
void AResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceNode::DamageHealth(float damage)
{
	health -= damage;
	if (bCheckIsDead(health))
	{
		//destroyable->DamageThreshold[0] = 0;
		//destroyable->DamageThreshold[1] = 0;
		//destroyable->DamageThreshold[2] = 0;
		
		this->Destroy();
	}
}

bool AResourceNode::bCheckIsDead(float healthRemaining)
{
	if (healthRemaining <= 0) { return true; }
	else {return false; }
}

