// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallPlayer.generated.h"


UCLASS()
class SUMOBALLS_API ABallPlayer : public APawn
{
	GENERATED_BODY()

	/** StaticMesh used for the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Ball;

	/** Spring arm for positioning the camera above the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera to view the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class URadialForceComponent* ForceHit;

public:
	// Sets default values for this pawn's properties
	ABallPlayer();

	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	float RollTorque;

	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	float ForceStrenght;

private:
	void MoveRight(float Val);

	void MoveForward(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveForward(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float Val);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
