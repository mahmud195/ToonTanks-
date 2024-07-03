// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABullet();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle collision events
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // Function to set the damage amount
    UFUNCTION(BlueprintCallable)
    void SetDamageAmount(float NewDamageAmount);

private:
    UPROPERTY(EditAnywhere)
    float DamageAmount = 10.0f;

    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere)
    class UCapsuleComponent* CapsuleComp;
};