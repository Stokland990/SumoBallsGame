// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBonus.generated.h"

UCLASS()
class SUMOBALLS_API ASpeedBonus : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* SpeedBonusEffect = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* CollectBonusEffect = nullptr;

public:	
	// Sets default values for this actor's properties
	ASpeedBonus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	float DestroyDelay = 5;

	class ABallPlayer* OverlapedBall;
};
