// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingComponentByBluePrint.h"

// Sets default values for this component's properties
URotatingComponentByBluePrint::URotatingComponentByBluePrint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotatingComponentByBluePrint::BeginPlay()

{
	Super::BeginPlay();

	// ...
	
}

void URotatingComponentByBluePrint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Your tick logic here
}


void URotatingComponentByBluePrint::RotateMesh(UStaticMeshComponent* MeshComponent, float MinAngle, float MaxAngle, float Speed, float DeltaTime)
{
    // Ensure that the mesh component is valid
    if (MeshComponent)
    {
        // Get the current rotation
        FRotator CurrentRotation = MeshComponent->GetRelativeRotation();

        // Calculate the target rotation based on the current angle and a rotation increment
        float CurrentAngle = FMath::Fmod(CurrentRotation.Yaw, 360.0f); // Ensure angle is within [0, 360)
        float TargetAngle = FMath::RandRange(MinAngle, MaxAngle);

        // Calculate the delta angle between the current angle and the target angle
        float DeltaAngle = FMath::Abs(TargetAngle - CurrentAngle);

        // Determine the direction of rotation (clockwise or counterclockwise)
        float RotationDirection = FMath::Sign(TargetAngle - CurrentAngle);

        // Calculate the rotation increment based on the desired rotation speed
        float RotationIncrement = RotationDirection * Speed * DeltaTime;

        // Check if the rotation should stop
        if (DeltaAngle <= FMath::Abs(RotationIncrement))
        {
            // If the remaining rotation is smaller than the increment, just set the target angle
            CurrentRotation.Yaw = TargetAngle;
        }
        else
        {
            // Otherwise, apply the rotation increment using spherical interpolation (Slerp)
            FRotator TargetRotation = FRotator(0.0f, TargetAngle, 0.0f);
            CurrentRotation = FQuat::Slerp(CurrentRotation.Quaternion(), TargetRotation.Quaternion(), FMath::Clamp(Speed * DeltaTime, 0.0f, 1.0f)).Rotator();
        }

        // Apply the new rotation to the mesh
        MeshComponent->SetRelativeRotation(CurrentRotation);
    }
    else
    {
        // Print a warning if the mesh component is invalid
        UE_LOG(LogTemp, Warning, TEXT("Invalid mesh component"));
    }
}










