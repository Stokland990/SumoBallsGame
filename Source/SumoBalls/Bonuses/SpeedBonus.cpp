// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedBonus.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Player/BallPlayer.h"
#include "Classes/Engine/World.h"
#include "TimerManager.h"

// Sets default values
ASpeedBonus::ASpeedBonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	RootComponent = TriggerBox;

	SpeedBonusEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("SpeedBonusEffect"));
	SpeedBonusEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollectBonusEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("CollectSpeedBonusEffect"));
	CollectBonusEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollectBonusEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASpeedBonus::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBonus::OnOverlapBegin);
}

// Called every frame
void ASpeedBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpeedBonus::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OverlapedBall = Cast<ABallPlayer>(OtherActor);
	if (OverlapedBall)
	{
		SpeedBonusEffect->DestroyComponent();
		CollectBonusEffect->Activate();
		TriggerBox->DestroyComponent();
		OverlapedBall->RollTorque = 70000000.f;
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASpeedBonus::OnTimerExpire, DestroyDelay, false);
	}
}

void ASpeedBonus::OnTimerExpire()
{
	OverlapedBall->RollTorque = 40000000.0f;
	Destroy();
}

