// Fill out your copyright notice in the Description page of Project Settings.


#include "AThirdPersonCharBase.h"
#include "AThirdPersonCharBase.h"
#include "EnemyCharBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ResourceNode.h"
#include "Animation/AnimInstanceProxy.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AThirdPersonCharBase::AThirdPersonCharBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	attackRate = -1;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

	maxStamina = 100.0f;
	anim = 0;
	maxStamina = 100;
	stamina = maxStamina;
	maxHealth = 100;
	health = maxHealth;
	maxHunger = 100;
	hunger = maxHunger;

}

// Called when the game starts or when spawned
void AThirdPersonCharBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
			subsystem->AddMappingContext(mappingContext, 0);

	
	
	anim = 0;
}

// Called every frame
void AThirdPersonCharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	hunger -= DeltaTime / 2;

	if (hunger > 100)
		hunger = 100;
	if (hunger < 0)
		hunger = 0;

	UpdateHungerSlider();	
	
}

// Called to bind functionality to input
void AThirdPersonCharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AThirdPersonCharBase::MoveCharacter);
		
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AThirdPersonCharBase::Look);

		enhancedInputComponent->BindAction(attackAction, ETriggerEvent::Triggered, this, &AThirdPersonCharBase::Attack);
		
		enhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Started, this, &AThirdPersonCharBase::Sprint);
		enhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Completed, this, &AThirdPersonCharBase::StopSprinting);

		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &AThirdPersonCharBase::Jump);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &AThirdPersonCharBase::StopJumping);
	
		enhancedInputComponent->BindAction(eatAction, ETriggerEvent::Started, this, &AThirdPersonCharBase::Eat);
	
	}
}

#pragma region Movement

void AThirdPersonCharBase::MoveCharacter(const FInputActionValue& Value)
{
	const FVector2D moveVector = Value.Get<FVector2D>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDir, moveVector.Y);
	AddMovementInput(rightDir, moveVector.X);
}

void AThirdPersonCharBase::Look(const FInputActionValue& Value)
{
	const FVector2D lookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(lookAxisVector.Y);
	AddControllerYawInput(lookAxisVector.X);
}

#pragma endregion 

#pragma region Sprint

void AThirdPersonCharBase::Sprint()
{
	bIsSprinting = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->MaxWalkSpeed *= sprintMultiplier;
}

void AThirdPersonCharBase::StopSprinting()
{
	bIsSprinting = false;

	followCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
}

#pragma endregion 

#pragma region Attack

void AThirdPersonCharBase::Attack()
{
	if (bIsAttacking || GetCharacterMovement()->IsFalling()) { return; }

	bIsAttacking = true;
	bUseControllerRotationYaw = true;
	
	GetCharacterMovement()->DisableMovement();

	if (anim == 0)
		PlayAnimMontage(attackAnim1, 1, NAME_None);
	else if (anim == 1)
		PlayAnimMontage(attackAnim2, 1, NAME_None);
}

void AThirdPersonCharBase::LightAttack()
{
	stamina -= 25;
	
	attackRate = 1;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	TArray<AActor*> outHit;

	if (UKismetSystemLibrary::SphereOverlapActors(
		GetController(),
		GetActorLocation(),
		200,
		objectTypes,
		nullptr,
		actorsToIgnore,
		outHit
		))
	{
		for (AActor* hitObj : outHit)
		{
			if (IsValid(hitObj))
			{
				if (AResourceNode* node = Cast<AResourceNode>(hitObj)) {

					if (!IsValid(node)) { return; }

					node->DamageHealth(ProcessDamage());

					if (node->bCheckIsDead()) {
						wood += node->wood;
						stone += node->stone;
						iron += node->iron;
						UpdateUI();
					}

					UpdateTarget(hitObj);
				}

				if (AEnemyCharBase* enemy = Cast<AEnemyCharBase>(hitObj))
				{
					if (!IsValid(enemy)) { return; }

					enemy->EnemyTakeDamage(ProcessDamage());
					UpdateTarget(hitObj);
				}
			}
		}
	}
	
}

void AThirdPersonCharBase::StopLightAttack()
{
	if (anim == 0)
		anim = 1;
	else if (anim == 1)
		anim = 0;
	
	GetCharacterMovement()->MovementMode = MOVE_Walking;
	bUseControllerRotationYaw = false;
	bIsAttacking = false;
}

float AThirdPersonCharBase::ProcessDamage()
{
	float newDamage = damage;
	if (hunger <= 100 && hunger > 70) {
		newDamage = damage;
	}
	else if (hunger < 70 && hunger > 50) {
		newDamage /= 1.2;
	}
	else if (hunger < 50 && hunger > 10) {
		newDamage /= 1.4;
	}
	else if (hunger < 10) {
		newDamage /= 2;
	}
	return newDamage;
}

FName AThirdPersonCharBase::ProcessHunger()
{
	FName name = "";

	if (hunger < 150 && hunger > 70) {
		name = "Full";
	}
	else if (hunger < 70 && hunger > 50) {
		name = "Hungry";
	}
	else if (hunger < 50 && hunger > 10) {
		name = "Starving";
	}
	else if (hunger < 10) {
		name = "Dying";
	}

	return name;
}

#pragma endregion

bool AThirdPersonCharBase::CheckCanBuy(float woodCost, float stoneCost, float ironCost)
{
	if (woodCost > wood || stoneCost > stone || ironCost > iron) { 
		return false;
	}
	else
	{
		return true;
	}
}

void AThirdPersonCharBase::BuyItem(float woodCost, float stoneCost, float ironCost)
{
	wood -= woodCost;
	stone -= stoneCost;
	iron -= ironCost;
	UpdateUI();
}

void AThirdPersonCharBase::DamageUpgrade()
{
	damage += 5;
}

void AThirdPersonCharBase::Eat()
{
	if (food > 0) {
		food--;
		hunger += 25;
		UpdateUI();
	}
}



