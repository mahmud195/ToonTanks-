#include "RotatingComponent.h"

// Sets default values for this component's properties
URotatingComponent::URotatingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    PrimaryComponentTick.bCanEverTick = true;
    RotationSpeed = 5.f;
    MinAngle = -45.f;
    MaxAngle = 45.f;
    CurrentAngle = 0.f;
    bIsIncreasing = true;
}

// Called when the game starts
void URotatingComponent::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void URotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdateOscillatingAngle(DeltaTime);
	RotateMeshByName(MeshName,RotationSpeed,RotationSpeed);
}

void URotatingComponent::RotateMeshByName(const FName& InMeshName, float Angle, float Speed)
{
    // Get all components attached to the owner actor
    TArray<UActorComponent*> Components;
    GetOwner()->GetComponents(Components);

    // Loop through all components to find the one with the specified name
    for (UActorComponent* Component : Components)
    {
        if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(Component))
        {
            if (MeshComponent->GetName() == InMeshName.ToString())
            {
                // Rotate the found mesh component
                RotateMeshComponent(MeshComponent, Angle, Speed);
                return; // Exit the function after finding and rotating the mesh
            }
        }
    }

    // If the function reaches this point, it means the mesh component was not found
    UE_LOG(LogTemp, Warning, TEXT("Mesh component named '%s' not found in owner actor for RotatingComponent: %s"), *InMeshName.ToString(), *GetOwner()->GetName());
}



void URotatingComponent::RotateMeshComponent(UStaticMeshComponent* MeshComponent, float Angle, float Speed)
{
    FRotator NewRotation = MeshComponent->GetComponentRotation();
    NewRotation.Yaw += Angle;
    MeshComponent->SetWorldRotation(NewRotation);
}

void URotatingComponent::UpdateOscillatingAngle(float DeltaTime)
{
    if (bIsIncreasing)
    {
        CurrentAngle += RotationSpeed * DeltaTime;
        if (CurrentAngle >= 1.f)
        {
            CurrentAngle = 1.f;
            bIsIncreasing = false;
        }
    }
    else
    {
        CurrentAngle -= RotationSpeed * DeltaTime;
        if (CurrentAngle <= 0.f)
        {
            CurrentAngle = 0.f;
            bIsIncreasing = true;
        }
    }
}