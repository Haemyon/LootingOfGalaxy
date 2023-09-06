// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

/*
 *	아이템에 사용될 내용들이 정의되어 있는 헤더입니다.
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

	//절대 중복되면 안 됨.
	UPROPERTY(EditAnywhere)
	FName Item_Code;

	UPROPERTY(EditAnywhere)
	EItemType Item_Type;
	//아이템 이미지
	UPROPERTY(EditAnywhere)
	class UTexture2D* Item_Image;
	//아이템 이름
	UPROPERTY(EditAnywhere)
	FString Item_Name;

	//아이템 설명
	UPROPERTY(EditAnywhere)
	FString Item_Description;
	UPROPERTY(EditAnywhere, meta = (Multiline = true))
	FString Item_Description_Long;

	//아이템 갯수
	UPROPERTY(VisibleAnywhere)
	int32 Item_Count;
	//아이템 가격
	UPROPERTY(EditAnywhere)
	int32 Item_Price;
};

USTRUCT(BlueprintType)
struct FGenericItemInformation
{
	GENERATED_BODY()
public:

	//아이템 구조체 공유 포인터.
	TSharedPtr<FItemInformation> P_ItemInfo;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItemActor> ItemActorObject;

	//절대 중복되면 안 됨.
	UPROPERTY(EditAnywhere)
	FName Item_Code;

	UPROPERTY(EditAnywhere)
	EItemType Item_Type;
	//아이템 이미지
	UPROPERTY(EditAnywhere)
	class UTexture2D* Item_Image;
	//아이템 이름
	UPROPERTY(EditAnywhere)
	FString Item_Name;

	//아이템 설명
	UPROPERTY(EditAnywhere)
	FString Item_Description;
	UPROPERTY(EditAnywhere, meta = (Multiline = true))
	FString Item_Description_Long;

	//아이템 갯수
	UPROPERTY(VisibleAnywhere)
	int32 Item_Count;
	//아이템 가격
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
	//무기의 외형
	UPROPERTY(EditAnywhere)
	class UStaticMesh* WeaponMesh;
	//무기의 애니메이션
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
