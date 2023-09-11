// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/00_Component/StatusComponent.h"

#include "LOG/LOGCharacter.h"
#include "LOG/00_Character/BaseCharacter.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStatusComponent::AddHP(float value)
{
	HP = FMath::Clamp(HP + value, 0.f, MaxHP);
	if (GetOwner()->IsA<ABaseCharacter>())
	{
		GetOwner<ABaseCharacter>()->OnChangedHP.Broadcast(this);
	}
	if (GetOwner()->IsA<ALOGCharacter>())
	{
		GetOwner<ALOGCharacter>()->PlayerChangedHP.Broadcast(this);
	}
}

void UStatusComponent::AddSP(float value)
{
}

void UStatusComponent::AddMP(float value)
{
}

// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

