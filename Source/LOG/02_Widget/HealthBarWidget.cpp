// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/02_Widget/HealthBarWidget.h"

#include "LOG/00_Character/00_Component/StatusComponent.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHPPercent(UStatusComponent* statComp)
{
	float per = statComp->GetHP() / statComp->GetMaxHP();
	ProgressBar_HP->SetPercent(per);
}
