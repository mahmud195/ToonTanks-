// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealth();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Function to apply damage to this actor's health
    UFUNCTION(BlueprintCallable)
    void TakeDamage(float DamageAmount);

    // Function to check if this actor's health is zero or below
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsDead() const;

private:
    UPROPERTY(EditAnywhere, Category = "Health")
    float DefaultHealth = 100.0f;

    float CurrentHealth;
};