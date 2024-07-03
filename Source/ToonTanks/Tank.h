// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Movement functions
	virtual void MoveForward(float Value);
	virtual void RotateRight(float Value) override;
	void Speed(float Value);

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USpringArmComponent *OurCameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent *OurCamera;
	UPROPERTY(EditAnywhere, Category = "Component")
	float MovementSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Component")
	float RotationSpeed = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class APlayerController* TankController;

	float speed;
	float normalspeed;
};
