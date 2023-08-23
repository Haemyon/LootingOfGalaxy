// Fill out your copyright notice in the Description page of Project Settings.

#include "LOG/00_Character/LOGPlayerController.h"
#include "LOG/00_Character/01_Widget/MainWidget.h"

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
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("MainWidget == nullptr"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MainWidgetObject == nullptr"));
	}
}
