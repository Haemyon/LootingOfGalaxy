// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

/*
 *	�����ۿ� ���� ������� ���ǵǾ� �ִ� ����Դϴ�.
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	CONSUME,
	EQUIPMENT,
	ETC
};


USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> ItemActorObject;

	//���� �ߺ��Ǹ� �� ��.
	UPROPERTY(EditAnywhere)
	FName Item_Code;

	UPROPERTY(EditAnywhere)
	EItemType Item_Type;
	//������ �̹���
	UPROPERTY(EditAnywhere)
	class UTexture2D* Item_Image;
	//������ �̸�
	UPROPERTY(EditAnywhere)
	FString Item_Name;

	//������ ����
	UPROPERTY(EditAnywhere)
	FString Item_Description;
	UPROPERTY(EditAnywhere, meta = (Multiline = true))
	FString Item_Description_Long;

	//������ ����
	UPROPERTY(VisibleAnywhere)
	int32 Item_Count;
	//������ ����
	UPROPERTY(EditAnywhere)
	int32 Item_Price;
};

USTRUCT(BlueprintType)
struct FGenericItemInformation
{
	GENERATED_BODY()
public:

	//������ ����ü ���� ������.
	TSharedPtr<FItemInformation> P_ItemInfo;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> ItemActorObject;

	//���� �ߺ��Ǹ� �� ��.
	UPROPERTY(EditAnywhere)
	FName Item_Code;

	UPROPERTY(EditAnywhere)
	EItemType Item_Type;
	//������ �̹���
	UPROPERTY(EditAnywhere)
	class UTexture2D* Item_Image;
	//������ �̸�
	UPROPERTY(EditAnywhere)
	FString Item_Name;

	//������ ����
	UPROPERTY(EditAnywhere)
	FString Item_Description;
	UPROPERTY(EditAnywhere, meta = (Multiline = true))
	FString Item_Description_Long;

	//������ ����
	UPROPERTY(VisibleAnywhere)
	int32 Item_Count;
	//������ ����
	UPROPERTY(EditAnywhere)
	int32 Item_Price;
};


UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	WEAPON,
	HELMET,
	LEG,
	CHEST,
	BULLETHOLDER,
	ACCESSORY,
};

USTRUCT(BlueprintType)
struct FEquipment : public FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EEquipmentType Equipment_Type;

	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	float Defence;
	UPROPERTY(EditAnywhere)
	float ActionSpeed;

	UPROPERTY(EditAnywhere)
	int32 Str;
	UPROPERTY(EditAnywhere)
	int32 Dex;
	UPROPERTY(EditAnywhere)
	int32 Wiz;

	UPROPERTY(EditAnywhere)
	float MaxHP;
	UPROPERTY(EditAnywhere)
	float MaxMP;
	UPROPERTY(EditAnywhere)
	float MaxSP;


};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	BOW,
	GRENADELUNCHER,
	MACHINGUN,
	MOBILEGRENADELUNCHER,
	PISTOL,
	RIPLE,
	ROCKETLUNCHER,
	SCOUTRIPLE,
	SHOTGUN,
	SUBMACHINGUN,
	SNIPERRIPLE
};

USTRUCT(BlueprintType)
struct FWeapon : public FEquipment
{
	GENERATED_BODY()
public:
	//������ ����
	UPROPERTY(EditAnywhere)
	class UStaticMesh* WeaponMesh;
	//������ �ִϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimBlueprint* AnimBlueprint;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* RollMontage;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* HitParticle;
	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	FName SocketName;

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
	float RollSP;
	UPROPERTY(EditAnywhere)
	float AttackSP;

	FWeapon()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::WEAPON;
	}

};

USTRUCT(BlueprintType)
struct FHelmet : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* HelmetMesh;

	FHelmet()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::HELMET;
	}

};

USTRUCT(BlueprintType)
struct FLeg : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* LegMesh;

	FLeg()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::LEG;
	}

};

USTRUCT(BlueprintType)
struct FChest : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* ChestMesh;

	FChest()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::CHEST;
	}

};

USTRUCT(BlueprintType)
struct FBulletholder : public FEquipment
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* BulletholderMesh;

	FBulletholder()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::BULLETHOLDER;
	}

};

USTRUCT(BlueprintType)
struct FAccessory : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* AccessoryMesh;

	FAccessory()
	{
		Item_Type = EItemType::EQUIPMENT;
		Equipment_Type = EEquipmentType::ACCESSORY;
	}
};

UENUM(BlueprintType)
enum class EConsumeType : uint8
{
	POTION,
	ETC
};

USTRUCT(BlueprintType)
struct FConsume : public FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EConsumeType ConsumeType;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* UseMontage;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* UseParticle;
	UPROPERTY(EditAnywhere)
	class USoundBase* UseSound;
};

USTRUCT(BlueprintType)
struct FPotion : public FConsume
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float RecoverHP;
	UPROPERTY(EditAnywhere)
	float RecoverMP;
	UPROPERTY(EditAnywhere)
	float RecoverSP;

};

UCLASS()
class LOG_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
};
