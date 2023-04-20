// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "AThirdPersonCharBase.generated.h"

UCLASS()
class AM_UNREAL_FINALPROJ_API AThirdPersonCharBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharBase();

	UPROPERTY(EditAnywhere, Category = "Input")
		UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* moveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* lookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* sprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* attackAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		USpringArmComponent* cameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		UCameraComponent* followCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		USphereComponent* sphereCol;
	
	UPROPERTY(EditAnywhere, Category="Movement")
		float sprintMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
		float stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
		float maxStamina;
	UPROPERTY(VisibleAnywhere, Category="Movement")
		bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
		UAnimMontage* attackAnim1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
		UAnimMontage* attackAnim2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
		UAnimMontage* hitAnim;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation")
		bool bIsAttacking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation")
		float attackRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
		int anim = 0; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
		float maxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
		float wood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
		float stone;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
		float iron;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
		float damage;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void MoveCharacter(const FInputActionValue& Value);
	UFUNCTION()
		void Look(const FInputActionValue& Value);
	
	void Sprint();
	void StopSprinting();

	UFUNCTION(BlueprintCallable)
		bool CheckCanBuy(float woodCost, float stoneCost, float ironCost);
	UFUNCTION(BlueprintCallable)
		void BuyItem(float woodCost, float stoneCost, float ironCost);

	UFUNCTION(BlueprintCallable)
		void DamageUpgrade();

	
	UFUNCTION(BlueprintImplementableEvent)
		void PlayAttackAnimEvent();
	UFUNCTION(BlueprintCallable)
		void Attack();
	UFUNCTION(BlueprintCallable)
		void LightAttack();
	UFUNCTION(BlueprintCallable)
		void StopLightAttack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateUI();
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateTarget(AActor* target);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};