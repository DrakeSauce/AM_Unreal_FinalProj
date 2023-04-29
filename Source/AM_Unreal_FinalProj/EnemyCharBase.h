// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharBase.generated.h"


UCLASS()
class AM_UNREAL_FINALPROJ_API AEnemyCharBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* hitAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool bIsHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float damage;

	UPROPERTY(EditAnywhere)
		float speedMultiplier;

	UFUNCTION(BlueprintCallable)
		void EnemyTakeDamage(float damageToTake);


};