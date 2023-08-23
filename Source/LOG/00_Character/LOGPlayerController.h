// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOG_API ALOGPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetObject;

	UPROPERTY()
	UMainWidget* MainWidget;

	//��Ʈ�ѷ��� �ش� ���� ���ǵǴ� ������ ȣ���.
	virtual void OnPossess(APawn* aPawn) override;
	
};