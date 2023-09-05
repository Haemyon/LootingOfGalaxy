// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LOG/00_Character/BaseCharacter.h"
#include "Engine/DataTable.h"
#include "Monster.generated.h"

//몬스터가 드롭할 아이템 구조체
USTRUCT(BlueprintType)
struct FDropItem : public FTableRowBase
{
	GENERATED_BODY()
public:
	//드롭할 아이템
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> itemToDrop;

	//아이템이 선택될 확률
	UPROPERTY(EditAnywhere)
	float percent;

};

USTRUCT(BlueprintType)
struct FGenericDropItem
{
	GENERATED_BODY()
public:
	//드롭할 아이템
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> itemToDrop;

	//아이템이 선택될 확률
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
	//사망 에니메이션
	UPROPERTY(EditAnywhere)
	class UAnimationAsset* DeadAnim;

	//메시에 겹침 이벤트가 발생했을 때 호출되는 함수.
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
 * @brief 테이블 내부 드롭 확률이 총 100%이하인지 확인합니다. 100%를 초과하는 확률을 가질 순 없습니다
 * @param List 테이블에 저장된 아이템들
 * @return 정상이면 참, 비정상이면 거짓
 */
	//bool CheckDropTablePercentIsOver(const TArray<FDropItem*> List);

	//아이템 드롭 테이블에서 값을 읽어와 세팅합니다.
	//virtual void InitDropItems();

	//아이템을 드롭합니다.
	//virtual void DropItem();

};
