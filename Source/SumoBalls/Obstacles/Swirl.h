// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Swirl.generated.h"

UCLASS()
class SUMOBALLS_API ASwirl : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		class UBoxComponent* DeathBox;

		UPROPERTY(VisibleAnywhere)
		class URadialForceComponent* MagnetForce;

		UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* SwirlEffect;

public:	
	// Sets default values for this actor's properties
	ASwirl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
