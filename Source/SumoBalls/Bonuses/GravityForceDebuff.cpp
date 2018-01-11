// Fill out your copyright notice in the Description page of Project Settings.

#include "GravityForceDebuff.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Player/BallPlayer.h"
#include "Classes/Engine/World.h"
#include "TimerManager.h"

AGravityForceDebuff::AGravityForceDebuff()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	RootComponent = TriggerBox;

	GravityDebuffEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("SpeedBonusEffect"));
	GravityDebuffEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollectDebuffEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("CollectSpeedBonusEffect"));
	CollectDebuffEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollectDebuffEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AGravityForceDebuff::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGravityForceDebuff::OnOverlapBegin);
}

// Called every frame
void AGravityForceDebuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGravityForceDebuff::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OverlapedBall = Cast<ABallPlayer>(OtherActor);
	if (OverlapedBall)
	{
		GravityDebuffEffect->DestroyComponent();
		CollectDebuffEffect->Activate();
		TriggerBox->DestroyComponent();
		OverlapedBall->ForceStrenght = -20000.f;
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AGravityForceDebuff::OnTimerExpire, DestroyDelay, false);
	}
}

void AGravityForceDebuff::OnTimerExpire()
{
	OverlapedBall->ForceStrenght = 20000.f;
	Destroy();
}

