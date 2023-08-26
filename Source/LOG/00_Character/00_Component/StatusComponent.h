// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	//스테이터스
protected:
	UPROPERTY(EditAnywhere)
	float HP = 80;
	UPROPERTY(EditAnywhere)
	float MaxHP = 100;
	UPROPERTY(EditAnywhere)
	float SP = 80;
	UPROPERTY(EditAnywhere)
	float MaxSP = 100;
	UPROPERTY(EditAnywhere)
	float MP = 80;
	UPROPERTY(EditAnywhere)
	float MaxMP = 100;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetHP() { return HP; }
	float GetMaxHP() { return MaxHP; }
	float GetSP() { return SP; }
	float GetMaxSP() { return MaxSP; }
	float GetMP() { return MP; }
	float GetMaxMP() { return MaxMP; }


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
