// Fill out your copyright notice in the Description page of Project Settings.

#include "LOG/00_Character/LOGPlayerController.h"

#include "LOG/LOGCharacter.h"
#include "LOG/00_Character/01_Widget/MainWidget.h"
#include "LOG/01_DataTable/LevelDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "LOG/00_Character/00_Component/StatusComponent.h"

void ALOGPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));

	if (MainWidgetObject != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set MainWidget"));
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetObject);
		if (MainWidget != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainWidget is AddToViewport"));
			MainWidget->AddToViewport();

			ALOGCharacter* player = Cast<ALOGCharacter>(aPawn);
			if (player != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Set player"));
				player->OnChangedHP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateHPPercent);
				player->OnChangedSP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateSPPercent);
				player->OnChangedMP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateMPPercent);

				MainWidget->UpdateHPPercent(player->GetStatusComponent());
				MainWidget->UpdateSPPercent(player->GetStatusComponent());
				MainWidget->UpdateMPPercent(player->GetStatusComponent());
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("MainWidget == nullptr"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MainWidgetObject == nullptr"));
	}

	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/02_DataTable/DT_LevelUp.DT_LevelUp"));
	//if (DataTable.Succeeded())
	//{
	//	LevelUpDataTable = DataTable.Object;
	//	UE_LOG(LogTemp, Error, TEXT("LevelUpDataTable == Succeeded"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("LevelUpDataTable == unllptr"));
	//}
}

void ALOGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
	//
	//if (LevelUpDataTable != nullptr)
	//{
	//	for (int32 i = 1; i <= 10; i++)
	//	{
	//		FLevelUpTableRow* LevelUpTableRow = LevelUpDataTable->FindRow<FLevelUpTableRow>(FName(*(FString::FormatAsNumber(i))), FString(""));
	//		UE_LOG(LogTemp, Log, TEXT("Lv.%d :: ExpToNextLevel(%d) TotalExp(%d)"), i, (*LevelUpTableRow).ExpToNextLevel, (*LevelUpTableRow).TotalEXP);
	//	}
	//}
}
