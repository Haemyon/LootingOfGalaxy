// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 *
 */
UCLASS()
class LOG_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UProgressBarWidget* UMG_ProgressBar;

public:
	UFUNCTION()
	void UpdateHPPercent(class UStatusComponent* statComp);
	UFUNCTION()
	void UpdateSPPercent(class UStatusComponent* statComp);
	UFUNCTION()
	void UpdateMPPercent(class UStatusComponent* statComp);
};
