// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SuckSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SuckSphereComp"));
	SuckSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);;
	SuckSphere->SetSphereRadius(1000);

	DestroySphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphere"));
	DestroySphere->SetSphereRadius(70);
	DestroySphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);;

	DestroySphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapDestroySphere);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::OverlapDestroySphere(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComps;
	SuckSphere->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = SuckSphere->GetScaledSphereRadius();
			const float ForceStrength = -20000;

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Linear, true);
		}
	}
}

