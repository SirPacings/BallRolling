// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlledBall.generated.h"

UCLASS()
class BALLROLLING_API AControlledBall : public AActor
{
	GENERATED_BODY()

	/** StaticMesh used for the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Ball;
	
public:	
	// Sets default values for this actor's properties
	AControlledBall();

	/** Torque to apply when trying to roll ball */
	UPROPERTY(EditAnywhere, Category = Ball)
	float RollTorque;

	/** Called for side to side input */
	void MoveRight(float Val, FVector CameraRight);

	/** Called to move ball forwards and backwards */
	void MoveForward(float Val, FVector CameraForward);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Ball subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBall() const { return Ball; }

};
