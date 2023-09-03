// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/02_Widget/DamageTextWidget.h"

#include "Components/TextBlock.h"

void UDamageTextWidget::SetDamageText(const float Damage)
{
	TextBlock_Damage->SetText(FText::AsNumber(Damage));
}
