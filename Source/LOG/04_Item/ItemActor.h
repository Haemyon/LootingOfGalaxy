// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemActor.generated.h"

UCLASS()
class LOG_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	//�÷��̾���� ��Ĩ�� Ȯ���� �ݸ���
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;
	//������ ��ƼŬ
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent;
	//�������� ���� �� �ִٴ� UI ǥ�ø� ���� ����������Ʈ
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComponent;

	//�� ���Ͱ� ������ �ִ� ������ �ڵ�
	UPROPERTY(EditAnywhere)
	FName Item_Code;
	//�� ī��Ʈ ��ŭ �÷��̾� �κ��丮�� ������ ������ �߰��˴ϴ�.
	UPROPERTY(EditAnywhere)
	int32 Item_Count = 1;

	//��� ������ ������ ����ִ� ���������̺��Դϴ�.
	UPROPERTY(EditAnywhere)
	class UDataTable* Item_Table;

	///������ ���� ������ ����ִ� ����ü
	//UPROPERTY(VisibleAnywhere)
	//FGenericItemInformation GenericItemInformation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	//�������Ʈ�� Construct�� ���� ������ �մϴ�.
	//�� �������Ʈ ������Ʈ ���� ������ ����Ǹ� ȣ��˴ϴ�.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/**
	 * @brief �÷��̾ ������ ���ÿ� ���� �� ���Ͱ� �����Ǵ°��,PostEditChangeProperty�� ȣ����� �ʾ� �� �Լ� ���ο��� �ٽ� ������ �ʱ�ȭ �մϴ�.
	 */
	virtual void PostInitializeComponents() override;
	/**
	 * @brief ���������̺��� �� ���Ͱ� ���� ������ �ڵ带 Ű�� �Ͽ� ������ ������ �����ɴϴ�. ������ ������ ������ GenericItemInformation������ ����˴ϴ�.
	 *	���� ������ ������ ���� ����Ǿ�� �� ������ �ٸ��� ������, ������ �������� �� �Լ��� �� ���� �ؾ� �մϴ�.
	 */
	virtual void InitItemInformation();

public:	
	UWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }
	FName GetItem_Code() const { return Item_Code; }
	//FGenericItemInformation& GetGenericItemInformation() const { return GenericItemInformation; }

	/**
	 * @brief ��󿡰� ������ ȿ���� �����մϴ�. ������ �������� �� �����ؼ� ����� �����մϴ�.
	 * @param Target ���
	 */
	UFUNCTION(BlueprintNativeEvent)
	void ApplyItem(class AActor* Target);
	virtual void ApplyItem_Implementation(class AActor* Target) {  }

protected:
	template<typename T>
	const T* GetItemInformation();
};

template <typename T>
const T* AItemActor::GetItemInformation()
{
	if (Item_Table != nullptr)
	{
		return Item_Table->FindRow<T>(Item_Code, "Cannot Find");
	}
	return nullptr;
}
