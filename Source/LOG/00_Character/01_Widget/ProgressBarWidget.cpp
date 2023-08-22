// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/01_Widget/ProgressBarWidget.h"

#include "LOG/00_Character/00_Component/StatusComponent.h"
#include "Components/ProgressBar.h"

void UProgressBarWidget::UpdateProgressHP(UStatusComponent* statComp)
{
	float per = statComp->GetHP() / statComp->GetMaxHP();
	ProgressBar_HP->SetPercent(per);
}

void UProgressBarWidget::UpdateProgressSP(UStatusComponent* statComp)
{
	float per = statComp->GetSP() / statComp->GetMaxSP();
	ProgressBar_SP->SetPercent(per);
}

void UProgressBarWidget::UpdateProgressMP(UStatusComponent* statComp)
{
	float per = statComp->GetMP() / statComp->GetMaxMP();
	ProgressBar_SP->SetPercent(per);
}
