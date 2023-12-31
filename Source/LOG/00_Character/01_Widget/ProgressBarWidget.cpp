// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/01_Widget/ProgressBarWidget.h"

#include "LOG/00_Character/00_Component/StatusComponent.h"
#include "LOG/LOGCharacter.h"
#include "Components/ProgressBar.h"

void UProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	ALOGCharacter* player = Cast<ALOGCharacter>(GetOwningPlayerPawn());
	if (player != nullptr) 
	{
		UStatusComponent* statComp = player->GetStatusComponent();
		if (statComp != nullptr)
		{
			ProgressBar_HP->SetPercent(statComp->GetHP() / statComp->GetMaxHP());
			ProgressBar_SP->SetPercent(statComp->GetSP() / statComp->GetMaxSP());
			ProgressBar_MP->SetPercent(statComp->GetMP() / statComp->GetMaxMP());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("player == nullptr"));
	}
	
}

void UProgressBarWidget::UpdateProgressHP(UStatusComponent* statComp)
{
	float per = statComp->GetHP() / statComp->GetMaxHP();
	UE_LOG(LogTemp, Log, TEXT("Set HP : %f"), per);
	//ProgressBar_HP->SetPercent(per);
}

void UProgressBarWidget::UpdateProgressSP(UStatusComponent* statComp)
{
	float per = statComp->GetSP() / statComp->GetMaxSP();
	UE_LOG(LogTemp, Log, TEXT("Set SP : %f"), per);
	//ProgressBar_SP->SetPercent(1);
}

void UProgressBarWidget::UpdateProgressMP(UStatusComponent* statComp)
{
	float per = statComp->GetMP() / statComp->GetMaxMP();
	UE_LOG(LogTemp, Log, TEXT("Set MP : %f"), per);
	//ProgressBar_SP->SetPercent(per);
}
