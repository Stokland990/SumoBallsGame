// Fill out your copyright notice in the Description page of Project Settings.

#include "BallPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Player/SM_Ball"));

	/// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->SetWorldScale3D(FVector(1.3));
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(1.f);
	Ball->SetLinearDamping(0.4);
	Ball->BodyInstance.MassScale = 1.f;
	//Ball->BodyInstance.MaxAngularVelocity = 1.f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	/// Create a camera boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->GetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility);
	SpringArm->bDoCollisionTest = true;
	SpringArm->bAbsoluteRotation = true; //Rotation of the ball should not affect rotation of the boom
	SpringArm->RelativeRotation = FRotator(-40.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 1400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.5; 

	///Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; 

	ForceHit = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ForceHit->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ForceHit->Radius = 200;
	ForceHit->SetVisibility(true);
	ForceHit->AddObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery_MAX);
	ForceHit->bAbsoluteRotation = true;

	///Set up forces
	RollTorque = 40000000.0f;
	ForceStrenght = 20000.f;
	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForceHit->ImpulseStrength = ForceStrenght;
	ForceHit->FireImpulse();
}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ABallPlayer::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABallPlayer::MoveForward);
}

void ABallPlayer::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorque(Torque);
	Server_MoveRight(Val);
}

void ABallPlayer::Server_MoveRight_Implementation(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorque(Torque);
}

bool ABallPlayer::Server_MoveRight_Validate(float Val)
{
	return true;
}

void ABallPlayer::MoveForward(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Ball->AddTorque(Torque);
	Server_MoveForward(Val);
}

void ABallPlayer::Server_MoveForward_Implementation(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Ball->AddTorque(Torque);
}

bool ABallPlayer::Server_MoveForward_Validate(float Val)
{
	return true;
}