// Bullet.cpp

#include "Bullet.h"
#include "Health.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);
    CapsuleComp->SetupAttachment(RootComponent);
    CapsuleComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        // Check if the other actor has a health component
        UHealth* HealthComponent = OtherActor->FindComponentByClass<UHealth>();
        if (HealthComponent)
        {
            // Apply damage to the health component
            HealthComponent->TakeDamage(DamageAmount);
            float TakenDamage = DamageAmount; // Get the damage taken
            if (HealthComponent->IsDead())
            {
                // If the actor is dead, enable physics simulation and destroy after a delay
                OtherActor->SetActorEnableCollision(true);
                OtherActor->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
                OtherActor->SetLifeSpan(2.0f);
            }

            // Log the damage taken
            FString DamageMessage = FString::Printf(TEXT("%s took %f damage"), *OtherActor->GetName(), TakenDamage);
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DamageMessage);
        }

        // Destroy the bullet
        Destroy();
    }
}

void ABullet::SetDamageAmount(float NewDamageAmount)
{
    DamageAmount = NewDamageAmount;
}





