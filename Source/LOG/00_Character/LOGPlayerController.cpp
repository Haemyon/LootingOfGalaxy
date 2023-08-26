// Fill out your copyright notice in the Description page of Project Settings.

#include "LOG/00_Character/LOGPlayerController.h"

#include "LOG/00_Character/01_Widget/MainWidget.h"
#include "LOG/00_Character/00_Component/StatusComponent.h"
#include "LOG/LOGCharacter.h"

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
				
				if (player->OnChangedHP.IsBound() && player->OnChangedSP.IsBound()) 
				{
					UE_LOG(LogTemp, Warning, TEXT("OnChangedHP is Bound"));
					if (!player->GetStatusComponent())
					{
						UE_LOG(LogTemp, Error, TEXT("StatusComponent is Not Found"));
					}
					UE_LOG(LogTemp, Log, TEXT("\n-----------Player Status----------\nHP : %f\nSP : %f\nMP : %f"), 
						player->GetStatusComponent()->GetHP(), player->GetStatusComponent()->GetSP(),
						player->GetStatusComponent()->GetMP());
					player->OnChangedHP.Broadcast(player->GetStatusComponent());
					player->OnChangedSP.Broadcast(player->GetStatusComponent());
					player->OnChangedMP.Broadcast(player->GetStatusComponent());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("OnChangedHP is Not Bound"));
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("MainWidget == nullptr"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MainWidgetObject == nullptr"));
	}
}
