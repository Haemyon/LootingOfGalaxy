// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOG_API UProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UProgressBar* ProgressBar_HP;
	UPROPERTY()
	class UProgressBar* ProgressBar_SP;
	UPROPERTY()
	class UProgressBar* ProgressBar_MP;
	UPROPERTY()
	class UProgressBar* ProgressBar_TEST;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void UpdateProgressHP(class UStatusComponent* statComp);
	void UpdateProgressSP(class UStatusComponent* statComp);
	void UpdateProgressMP(class UStatusComponent* statComp);

};
