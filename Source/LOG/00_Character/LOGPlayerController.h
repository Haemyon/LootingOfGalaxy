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

	//컨트롤러가 해당 폰에 빙의되는 시점에 호출됨.
	virtual void OnPossess(APawn* aPawn) override;

	virtual void BeginPlay() override;

private:
	class UDataTable* LevelUpDataTable;

public:
	UMainWidget* GetMainWidget() { return MainWidget; }
	
};
