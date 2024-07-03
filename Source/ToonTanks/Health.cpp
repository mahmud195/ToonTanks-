// Health.cpp

#include "Health.h"

// Sets default values
UHealth::UHealth()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealth::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = DefaultHealth;
}

// Function to apply damage to this actor's health
void UHealth::TakeDamage(float DamageAmount)
{
    CurrentHealth -= DamageAmount;
    if (CurrentHealth <= 0)
    {
        // If health is zero or below, consider the actor dead
        CurrentHealth = 0;
    }
}

// Function to check if this actor's health is zero or below
bool UHealth::IsDead() const
{
    return CurrentHealth <= 0;
}

