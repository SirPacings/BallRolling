// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledBall.h"

// Sets default values
AControlledBall::AControlledBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Rolling/Meshes/BallMesh.BallMesh"));

	// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	// Set up forces
	RollTorque = 8000000.0f;
}

// Called when the game starts or when spawned
void AControlledBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControlledBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AControlledBall::MoveRight(float Val, FVector CameraForward)
{
	const FVector Torque = FVector(Val * RollTorque * -1 * CameraForward.X, Val * RollTorque * -1 * CameraForward.Y, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

void AControlledBall::MoveForward(float Val, FVector CameraRight)
{
	const FVector Torque = FVector(Val * RollTorque * CameraRight.X, Val * RollTorque* CameraRight.Y, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

