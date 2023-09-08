// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/03_Component/DamageBoxComponent.h"

#include "LOG/LOGCharacter.h"
#include "LOG/00_Character/00_Component/StatusComponent.h"

UDamageBoxComponent::UDamageBoxComponent()
{
	InitBoxExtent(FVector(100.f, 100.f, 100.f));
}

void UDamageBoxComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UDamageBoxComponent::OnSphereBeginOverlap);
}

void UDamageBoxComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALOGCharacter* Character = Cast<ALOGCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnDamageFloor.Broadcast(Character);
		UE_LOG(LogTemp, Error, TEXT("Damage Box Component Overlaped"));
		//auto StatusComp = Character->GetStatusComponent();
		//if (StatusComp != nullptr)
		//{
		//	Character->GetStatusComponent()->AddHP(-20);
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Error, TEXT("StatusComp == nullptr"));
		//}
	}
}

