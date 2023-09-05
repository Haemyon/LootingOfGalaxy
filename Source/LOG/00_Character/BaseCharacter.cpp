// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/BaseCharacter.h"

#include "00_Component/StatusComponent.h"
#include "LOG/02_Widget/DamageTextWidget.h"
#include "Components/WidgetComponent.h"
#include "Engine/EngineTypes.h"
#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(150, 15));
	HealthBarWidgetComponent->SetVisibility(false);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	FHitResult Hit;
	//FVector OutImpulseDir;
	//DamageEvent.GetBestHitInfo(this, DamageCauser, Hit, OutImpulseDir);
	//
	if (DamageTextWidgetComponentObject != nullptr)
	{
	
		UWidgetComponent* widgetComp = NewObject<UWidgetComponent>(this, DamageTextWidgetComponentObject);
		if (widgetComp != nullptr)
		{
			//������Ʈ ���������� �ݵ�� ȣ��.
			widgetComp->RegisterComponent();
			widgetComp->SetWorldLocation(Hit.Location);
	
			//���� ������Ʈ ���� ���� ������ �����ͼ�, �ؽ�Ʈ�� ���ط����� ����.
			UDamageTextWidget* widget = Cast<UDamageTextWidget>(widgetComp->GetUserWidgetObject());
			if (widget != nullptr)
			{
				widget->SetDamageText(DamageAmount);
			}
		}
	}
	
	//1. DamageAmount��ŭ ü���� ����.
	StatusComponent->AddHP((-1) * DamageAmount);
	//2. ���� ü���� �α׷� ����.
	UE_LOG(LogTemp, Log, TEXT("HP : %f"), StatusComponent->GetHP());
	
	//ü���� 0���϶��,
	if (StatusComponent->GetHP() <= 0.f)
	{
		//���ó���� �մϴ�.
		OnDead.Broadcast(EventInstigator->GetPawn());
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

	HealthBarWidgetComponent->SetVisibility(true);
	
	//Ÿ�̸� ������ ���� ���� Ÿ�̸Ӱ� ������, ���߰� �ٽ� ������
	if (GetWorldTimerManager().TimerExists(HealthBarWidgetVisibleTimerHandle)) {
		GetWorldTimerManager().ClearTimer(HealthBarWidgetVisibleTimerHandle);
	}
	
	FTimerDelegate VisibleTimerDel = FTimerDelegate::CreateUObject(
		HealthBarWidgetComponent,
		&UWidgetComponent::SetVisibility, false, false);
	GetWorldTimerManager().SetTimer(HealthBarWidgetVisibleTimerHandle, VisibleTimerDel, 3.f, false);
	
	

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnDead.AddUniqueDynamic(this, &ABaseCharacter::OnDeadEvent);
}
