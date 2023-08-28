// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "LevelDataTable.generated.h"

USTRUCT(BlueprintType)
struct FLevelUpTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUp")
	int32 ExpToNextLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUp")
	int32 TotalEXP;
};

UCLASS()
class LOG_API ALevelDataTable : public AActor
{
	GENERATED_BODY()
	
};
