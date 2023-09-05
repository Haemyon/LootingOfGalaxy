// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

//체력이 변하면 사용되는 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
//캐릭터가 사망했을때 사용할 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, class AActor*, EventInstigator);

UCLASS()
class LOG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//캐릭터의 체력상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnChangedHP OnChangedHP;

	//캐릭터 사망시 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

protected:
	//델리게이트에 저장할 함수
	UFUNCTION()
	virtual void OnChangedHPEvent(class UStatusComponent* statComp) { }
	UFUNCTION()
	virtual void OnDeadEvent(class AActor* EventInstigator) { }

	//캐릭터의 상태정보를 기억하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStatusComponent* StatusComponent;

	//캐릭터 머리위에 체력표시줄을 띄우기 위한 위젯 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* HealthBarWidgetComponent;

	//UWidgetComponent를 상속받은 오브젝트를 가져옴
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWidgetComponent> DamageTextWidgetComponentObject;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UStatusComponent* GetStatusComponent() { return StatusComponent; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void PostInitializeComponents() override;

	//피해를 입었을 때 보여지는 체력표시줄을 N초 후 숨기기 위한 타이머 핸들
	UPROPERTY()
	FTimerHandle HealthBarWidgetVisibleTimerHandle;

};
