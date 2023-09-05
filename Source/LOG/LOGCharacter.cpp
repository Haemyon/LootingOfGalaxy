// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOG/LOGCharacter.h"

#include "LOGProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LOG/00_Character/00_Component/StatusComponent.h"
#include "LOG/00_Character/LOGPlayerController.h"
#include "LOG/00_Character/01_Widget/MainWidget.h"
#include "LOG/02_Widget/DamageTextWidget.h"
#include "LOG/02_Widget/HealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


//////////////////////////////////////////////////////////////////////////
// ALOGCharacter

ALOGCharacter::ALOGCharacter()
{

	// Character doesnt have a rifle at start
	bHasRifle = false;

	bSprint = false;
	SprintMultiply = 1.5;

	bCrouch = false;
	CrouchMultiply = 0.5;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

}

void ALOGCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void ALOGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALOGCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALOGCharacter::Look);

		//Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ALOGCharacter::Sprint);

		//Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ALOGCharacter::Crouch);

	}
}

float ALOGCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	FHitResult Hit;
	StatusComponent->AddHP((-1) * DamageAmount);
	UE_LOG(LogTemp, Log, TEXT("HP : %f"), StatusComponent->GetHP());

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void ALOGCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);


		//UE_LOG(LogTemp, Log, TEXT("Movement"));
	}
}

void ALOGCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		//UE_LOG(LogTemp, Log, TEXT("Look"));
	}
}

void ALOGCharacter::Sprint(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (bCrouch == false)
		{
			if (bSprint == false)
			{
				GetCharacterMovement()->MaxWalkSpeed *= SprintMultiply;

				float speed = GetCharacterMovement()->MaxWalkSpeed;
				float HP = GetStatusComponent()->GetSP();
				UE_LOG(LogTemp, Log, TEXT("MaxWalkSpeed : %f\nCurrentHP : %f"), speed, HP);
				bSprint = true;
			}
			else
			{
				GetCharacterMovement()->MaxWalkSpeed /= SprintMultiply;
				float speed = GetCharacterMovement()->MaxWalkSpeed;
				UE_LOG(LogTemp, Log, TEXT("MaxWalkSpeed : %f"), speed);
				bSprint = false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Doing Another Action"));
		}
	}
}

void ALOGCharacter::Crouch(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (bSprint == false)
		{
			if (bCrouch == false)
			{
				UE_LOG(LogTemp, Log, TEXT("Crouch"));
				GetCharacterMovement()->MaxWalkSpeed *= CrouchMultiply;
				FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 30.f)); // Position the camera
				GetCapsuleComponent()->SetCapsuleHalfHeight(48.f);

				bCrouch = true;
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("UnCrouch"));
				GetCharacterMovement()->MaxWalkSpeed /= CrouchMultiply;
				FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
				GetCapsuleComponent()->SetCapsuleSize(55.f, 96.f);
				bCrouch = false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Doing Another Action"));
		}
	}
}

void ALOGCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ALOGCharacter::GetHasRifle()
{
	return bHasRifle;
}