#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePawn.h"
#include "Turret.generated.h"
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
    GENERATED_BODY()

public:
    ATurret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    float Radius;

    UPROPERTY(EditAnywhere)
    float MoveSpeed;

    UPROPERTY(EditAnywhere)
    float MinAngle;

    UPROPERTY(EditAnywhere)
    float MaxAngle;

    UPROPERTY(EditAnywhere)
    float InterpolationSpeed;

    UFUNCTION(BlueprintCallable)
    void FireIfPlayerInRange();

private:
    FVector FollowingPoint;

    FTimerHandle FireTimerHandle;

    bool bCanFire;

    void Fire();

    void ResetFire();
};