// Fill out your copyright notice in the Description page of Project Settings.


#include "LOG/00_Character/Monster.h"

#include "LOG//00_Character/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "LOG/02_Widget/HealthBarWidget.h"

AMonster::AMonster()
{
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AMonster::OnMeshComponentOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnChangedHP.AddUniqueDynamic(this, &AMonster::OnChangedHPEvent);
	HealthBarWidgetComponent->InitWidget();
	OnChangedHP.Broadcast(StatusComponent);

	GetMesh()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMonster::OnMeshComponentOverlapEvent);

	//��� ������ ����� �ʱ�ȭ �մϴ�.
	InitDropItems();
}

void AMonster::OnChangedHPEvent(UStatusComponent* statComp)
{
	UUserWidget* widget = HealthBarWidgetComponent->GetUserWidgetObject();
	if (widget != nullptr)
	{
		UHealthBarWidget* HpWidget = Cast<UHealthBarWidget>(widget);
		if (HpWidget != nullptr)
		{
			HpWidget->SetHPPercent(statComp);
		}
	}
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	FHitResult Hit;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMonster::OnDeadEvent(AActor* EventInstigator)
{
	Super::OnDeadEvent(EventInstigator);
	UE_LOG(LogTemp, Log, TEXT("Dead"));

	//�� �̻� �÷��̾���� ��ȣ�ۿ��� �Ͼ�� �ʵ��� �ݸ��� ������ �ٲߴϴ�.
	GetMesh()->SetCollisionProfileName("Spectator");

	//��� ���ϸ��̼� ���. ��Ÿ�ְ� �ƴ� �ִ� ������ ����ϸ�, �ִϸ��̼��� ������ �������� �����˴ϴ�.
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//GetMesh()->PlayAnimation(DeadAnim, false);

	//�������� ����մϴ�.
	DropItem();


	//5�ʵ� ����
	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &AMonster::K2_DestroyActor, 0.1f);
	UE_LOG(LogTemp, Log, TEXT("Monster Destroy"));
}

bool AMonster::CheckDropTablePercentIsOver(const TArray<FDropItem*> List)
{
	float Sum = 0;
	for (const auto Item : List)
	{
		Sum += Item->percent;
	}

	return Sum <= 100.f;
}

void AMonster::InitDropItems()
{
	if (DropTable != nullptr)
	{
		//���̺��� ��� ���� ������ �����մϴ�.
		TArray<FDropItem*> DropList;
		DropTable->GetAllRows<FDropItem>("", DropList);

		//������ ��� Ȯ���� �������� Ȯ���մϴ�.
		if (CheckDropTablePercentIsOver(DropList))
		{
			for (const auto Item : DropList)
			{
				DropItems.Emplace(FGenericDropItem(Item));
			}
		}
	}
}

void AMonster::DropItem()
{
	//��� �������� ����� ������ �������� 1~10���� ���մϴ�.
	const int32 randCount = FMath::RandRange(1, 10);

	//������ Ƚ����ŭ ����� �������� �����մϴ�.
	for (int32 i = 0; i < randCount; i++) {

		//���� Ȯ���� ���ؼ� ����� �������� �����մϴ�.
		const float rand = FMath::RandRange(1.f, 100.f);
		//UE_LOG(LogTemp, Log, TEXT("rand : %f"), rand);
		float sum = 0;
		for (auto Item : DropItems) {
			sum += Item.percent;
			//UE_LOG(LogTemp, Log, TEXT("sum : %f"), sum);
			if (rand <= sum) {
				FActorSpawnParameters SpawnParam;
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				FVector SpawnLocation = GetActorLocation();
				SpawnLocation.Z += 50.f;
				GetWorld()->SpawnActor<AItemActor>(Item.itemToDrop, SpawnLocation, FRotator::ZeroRotator, SpawnParam);
				break;
			}
		}
	}
}
