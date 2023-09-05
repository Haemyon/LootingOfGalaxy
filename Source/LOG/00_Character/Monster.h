// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LOG/00_Character/BaseCharacter.h"
#include "Engine/DataTable.h"
#include "Monster.generated.h"

//���Ͱ� ����� ������ ����ü
USTRUCT(BlueprintType)
struct FDropItem : public FTableRowBase
{
	GENERATED_BODY()
public:
	//����� ������
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> itemToDrop;

	//�������� ���õ� Ȯ��
	UPROPERTY(EditAnywhere)
	float percent;

};

USTRUCT(BlueprintType)
struct FGenericDropItem
{
	GENERATED_BODY()
public:
	//����� ������
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> itemToDrop;

	//�������� ���õ� Ȯ��
	UPROPERTY(EditAnywhere)
	float percent;

	FGenericDropItem() {}
	FGenericDropItem(const FDropItem* Item)
	{
		//this->itemToDrop = Item->itemToDrop;
		//this->percent = Item->percent;
	}
};

UCLASS()
class LOG_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonster();

protected:
	//��� ���ϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimationAsset* DeadAnim;

	//�޽ÿ� ��ħ �̺�Ʈ�� �߻����� �� ȣ��Ǵ� �Լ�.
	UFUNCTION()
	void OnMeshComponentOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	virtual void PostInitializeComponents() override;

	virtual void OnChangedHPEvent(class UStatusComponent* statComp) override;

	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void OnDeadEvent(AActor* EventInstigator) override;

	UPROPERTY(EditAnywhere)
	class UDataTable* DropTable;

	UPROPERTY()
	TArray<FGenericDropItem> DropItems;

	/**
 * @brief ���̺� ���� ��� Ȯ���� �� 100%�������� Ȯ���մϴ�. 100%�� �ʰ��ϴ� Ȯ���� ���� �� �����ϴ�
 * @param List ���̺� ����� �����۵�
 * @return �����̸� ��, �������̸� ����
 */
	//bool CheckDropTablePercentIsOver(const TArray<FDropItem*> List);

	//������ ��� ���̺��� ���� �о�� �����մϴ�.
	//virtual void InitDropItems();

	//�������� ����մϴ�.
	//virtual void DropItem();

};
