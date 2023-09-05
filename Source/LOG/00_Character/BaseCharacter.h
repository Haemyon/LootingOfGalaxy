// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

//ü���� ���ϸ� ���Ǵ� ��������Ʈ ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
//ĳ���Ͱ� ��������� ����� ��������Ʈ ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, class AActor*, EventInstigator);

UCLASS()
class LOG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//ĳ������ ü�»�Ȳ�� ���ϸ� ����Ǵ� ��������Ʈ
	UPROPERTY(BlueprintAssignable)
	FOnChangedHP OnChangedHP;

	//ĳ���� ����� ȣ��Ǵ� ��������Ʈ
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

protected:
	//��������Ʈ�� ������ �Լ�
	UFUNCTION()
	virtual void OnChangedHPEvent(class UStatusComponent* statComp) { }
	UFUNCTION()
	virtual void OnDeadEvent(class AActor* EventInstigator) { }

	//ĳ������ ���������� ����ϴ� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStatusComponent* StatusComponent;

	//ĳ���� �Ӹ����� ü��ǥ������ ���� ���� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* HealthBarWidgetComponent;

	//UWidgetComponent�� ��ӹ��� ������Ʈ�� ������
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

	//���ظ� �Ծ��� �� �������� ü��ǥ������ N�� �� ����� ���� Ÿ�̸� �ڵ�
	UPROPERTY()
	FTimerHandle HealthBarWidgetVisibleTimerHandle;

};
