// Fill out your copyright notice in the Description page of Project Settings.

#include "Swirl.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASwirl::ASwirl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = DeathBox;
	DeathBox->InitBoxExtent(FVector(30));
	DeathBox->SetWorldScale3D(FVector(1.5));

	MagnetForce = CreateDefaultSubobject<URadialForceComponent>(FName("Magnet Force"));
	MagnetForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MagnetForce->Radius = 800.f;
	MagnetForce->ImpulseStrength = -65000;
	MagnetForce->AddObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery_MAX);

	SwirlEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Swirl Effect"));
	SwirlEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ASwirl::BeginPlay()
{
	Super::BeginPlay();
	DeathBox->OnComponentBeginOverlap.AddDynamic(this, &ASwirl::OnOverlapBegin);
}

// Called every frame
void ASwirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MagnetForce->FireImpulse();
}

void ASwirl::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OtherActor->Destroy();
}

