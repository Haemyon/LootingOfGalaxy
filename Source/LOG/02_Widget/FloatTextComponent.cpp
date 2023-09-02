// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/02_Widget/FloatTextComponent.h"

UFloatTextComponent::UFloatTextComponent()
{
	InitBoxExtent(FVector(100.f, 100.f, 100.f));
}

void UFloatTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UFloatTextComponent::OnSphereBeginOverlap);
}

void UFloatTextComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALOGCharacter* Character = Cast<ALOGCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnFloatText.Broadcast(Character);
	}
}
