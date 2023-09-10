// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LOGCharacter.generated.h"

//체력이 변하면 사용되는 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
//실드가 변하면 사용되는 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedSP, class UStatusComponent*, statComp);
//마나가 변하면 사용되는 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedMP, class UStatusComponent*, statComp);

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ALOGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementComponent, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

public:
	ALOGCharacter();

	//캐릭터의 체력상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnChangedHP OnChangedHP;
	//캐릭터의 실드상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnChangedSP OnChangedSP;
	//캐릭터의 마나상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnChangedMP OnChangedMP;
	
protected:
	UFUNCTION()
	virtual void OnChangedHPEvent(class UStatusComponent* statComp) { }
	UFUNCTION()
	virtual void OnChangedSPEvent(class UStatusComponent* statComp) { }
	UFUNCTION()
	virtual void OnChangedMPEvent(class UStatusComponent* statComp) { }



public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStatusComponent* StatusComponent;

	UStatusComponent* GetStatusComponent() { return StatusComponent; }


protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Bool for Sprint */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	bool bSprint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float SprintMultiply;

	/** Bool for Crouch */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = input)
	bool bCrouch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = input)
	float CrouchMultiply;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Sprint input */
	void Sprint(const FInputActionValue& Value);

	/** Crouch for Sprint input */
	void Crouch(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};

