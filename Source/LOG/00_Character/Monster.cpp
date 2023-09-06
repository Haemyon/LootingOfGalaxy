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

	//드롭 아이템 목록을 초기화 합니다.
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

	//더 이상 플레이어와의 상호작용이 일어나지 않도록 콜리전 설정을 바꿉니다.
	GetMesh()->SetCollisionProfileName("Spectator");

	//사망 에니메이션 재생. 몽타주가 아닌 애님 에셋을 재생하면, 애니메이션의 마지막 프레임이 유지됩니다.
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//GetMesh()->PlayAnimation(DeadAnim, false);

	//아이템을 드롭합니다.
	DropItem();


	//5초뒤 제거
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
		//테이블에서 모든 행을 가져와 저장합니다.
		TArray<FDropItem*> DropList;
		DropTable->GetAllRows<FDropItem>("", DropList);

		//아이템 드롭 확률이 정상인지 확인합니다.
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
	//몇개의 아이템을 드롭할 것인지 랜덤으로 1~10개를 정합니다.
	const int32 randCount = FMath::RandRange(1, 10);

	//정해진 횟수만큼 드롭할 아이템을 결정합니다.
	for (int32 i = 0; i < randCount; i++) {

		//누적 확률을 통해서 드롭할 아이템을 선택합니다.
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
