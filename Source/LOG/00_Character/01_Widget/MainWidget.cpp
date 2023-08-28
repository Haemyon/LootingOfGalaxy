// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/01_Widget/MainWidget.h"

#include "LOG/00_Character/01_Widget/ProgressBarWidget.h"


void UMainWidget::UpdateHPPercent(UStatusComponent* statComp)
{
	UMG_ProgressBar->UpdateProgressHP(statComp);
}

void UMainWidget::UpdateSPPercent(UStatusComponent* statComp)
{
	UMG_ProgressBar->UpdateProgressSP(statComp);
}

void UMainWidget::UpdateMPPercent(UStatusComponent* statComp)
{
	UMG_ProgressBar->UpdateProgressMP(statComp);
}
