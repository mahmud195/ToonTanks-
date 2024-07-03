// RotatingComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API URotatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    // Sets default values for this component's properties
    URotatingComponent();

    // Rotate the mesh component by name with specified angle and speed
    UFUNCTION(BlueprintCallable, Category = "Rotation")
    void RotateMeshByName(const FName& MeshName, float Angle, float Speed);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UPROPERTY(EditAnywhere)
    FName MeshName;
private:
    UPROPERTY(EditAnywhere)
    float RotationSpeed;
    
    float MinAngle;
    float MaxAngle;
    float CurrentAngle;
    bool bIsIncreasing;

    // Rotate the specified mesh component by angle and speed
    void RotateMeshComponent(UStaticMeshComponent* MeshComponent, float Angle, float Speed);
    // Update the oscillating angle for rotation
    void UpdateOscillatingAngle(float DeltaTime);
};