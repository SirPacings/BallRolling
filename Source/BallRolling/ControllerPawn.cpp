// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerPawn.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// Sets default values
AControllerPawn::AControllerPawn()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera


}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetInstigator();
	Ball1 = GetWorld()->SpawnActor<AControlledBall>(BallClass, GetActorLocation()+(10,-50,0), GetActorRotation(), SpawnParams);
	Ball2 = GetWorld()->SpawnActor<AControlledBall>(BallClass, GetActorLocation() + (0, 50, 0), GetActorRotation(), SpawnParams);

}

// Called every frame
void AControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Ball1Location = Ball1->GetActorLocation();
	FVector Ball2Location = Ball2->GetActorLocation();
	FVector Midpoint = (Ball1Location +Ball2Location)/2;
	float dot = Dot3(Ball1Location, Ball2Location); // (Ball1Location.X * Ball2Location.X) + (Ball1Location.Y * Ball2Location.Y) + (Ball1Location.Z * Ball2Location.Z);
	float Ball1ZDst = Ball1Location.Size(); // sqrt(pow(Ball1Location.X, 2) + pow(Ball1Location.Y, 2) + pow(Ball1Location.Z, 2));
	float Ball2ZDst = Ball2Location.Size(); // sqrt(pow(Ball2Location.X, 2) + pow(Ball2Location.Y, 2) + pow(Ball2Location.Z, 2));

	FVector NormalBall1 = Ball1Location / Ball1ZDst;
	FVector NormalBall2 = Ball2Location / Ball2ZDst;

	FVector CrossProduct = FVector::CrossProduct(NormalBall1, NormalBall2);

	float DistBetween = sqrt(pow(Ball1Location.X-Ball2Location.X, 2) + pow(Ball1Location.Y - Ball2Location.Y, 2) + pow(Ball1Location.Z - Ball2Location.Z, 2));
	Camera->SetWorldLocation(Midpoint+(200,0,500));
	Camera->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Midpoint + (200, 0, 500),Midpoint));

	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, "DotProduct:" + FString::SanitizeFloat(dot/ Ball1ZDst * Ball2ZDst));

	DrawDebugLine(GetWorld(), Midpoint, Midpoint + 50*CrossProduct,FColor::Blue,false, -1, 0, 12.333);

	//Between length + Line
	DrawDebugLine(GetWorld(), Ball1Location, Ball2Location, FColor(255, 0, 0), false, -1, 0, 12.333);
	DrawDebugString(GetWorld(), (Ball1Location + Ball2Location) / 2, FString::SanitizeFloat(DistBetween),NULL,FColor::White, DeltaTime, false, 1);

	//Ball1 length + Line
	DrawDebugLine(GetWorld(), Ball1Location, FVector(0,0,0), FColor(255, 0, 0), false, -1, 0, 12.333);
	DrawDebugString(GetWorld(), Ball1Location / 2, FString::SanitizeFloat(Ball1Location.Size()), NULL, FColor::White, DeltaTime, false, 1);

	//Ball2 length + Line
	DrawDebugLine(GetWorld(), Ball2Location, FVector(0, 0, 0), FColor(255, 0, 0), false, -1, 0, 12.333);
	DrawDebugString(GetWorld(), Ball2Location / 2, FString::SanitizeFloat(Ball2Location.Size()), NULL, FColor::White, DeltaTime, false, 1);
}

// Called to bind functionality to input
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveRight", this, &AControllerPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AControllerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight2", this, &AControllerPawn::MoveRight2);
	PlayerInputComponent->BindAxis("MoveForward2", this, &AControllerPawn::MoveForward2);

}

void AControllerPawn::MoveRight(float Val)
{
	Ball1->MoveRight(Val, Camera->GetForwardVector());
}

void AControllerPawn::MoveForward(float Val)
{
	Ball1->MoveForward(Val, Camera->GetRightVector());
}

void AControllerPawn::MoveRight2(float Val)
{
	Ball2->MoveRight(Val, Camera->GetForwardVector());
}

void AControllerPawn::MoveForward2(float Val)
{
	Ball2->MoveForward(Val, Camera->GetRightVector());
}