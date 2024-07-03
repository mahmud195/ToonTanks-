// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Bullet.h"
ABasePawn::ABasePawn()
{
    
    PrimaryActorTick.bCanEverTick = true;
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::BeginPlay()
{
    Super::BeginPlay();
}

void ABasePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ABasePawn::RotateRight(float Value)
{
    
}

void ABasePawn::RotateTurretToTarget(const FVector& TargetLocation)
{
    FVector DirectionToTarget = TargetLocation - TurretMesh->GetComponentLocation();
    DirectionToTarget.Z = 0; 

   
    FRotator TurretRotation = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();

   
    FRotator NewRotation(0, TurretRotation.Yaw, 0);

    TurretMesh->SetWorldRotation(NewRotation);
}

// Include your Projectile class header file here

void ABasePawn::Fire()
{
    if (ProjectileClass)
    {
        // Spawn the projectile
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Instigator = this;
        ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (Projectile)
        {
            // Set the projectile's initial direction to be the same as the turret's forward vector
            FVector ProjectileDirection = TurretMesh->GetForwardVector();
        }
    }
}


