#include "Turret.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATurret::ATurret()
{
    PrimaryActorTick.bCanEverTick = true;

    Radius = 100.0f;
    MoveSpeed = 50.0f;
    MinAngle = 0.0f;
    MaxAngle = 180.0f;
    InterpolationSpeed = 2.0f;
    bCanFire = true; // Add a boolean flag to track if the turret can fire

    // Initialize BaseMesh and TurretMesh
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    TurretMesh->SetupAttachment(BaseMesh);
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    FollowingPoint = GetActorLocation() + FVector(Radius, 0.0f, 0.0f);
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ATank* PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerTank)
    {
        float DistanceToPlayer = FVector::Distance(GetActorLocation(), PlayerTank->GetActorLocation());
        if (DistanceToPlayer < 1000.0f && bCanFire) // Check if the turret can fire
        {
            FollowingPoint = FMath::Lerp(FollowingPoint, PlayerTank->GetActorLocation(), DeltaTime * InterpolationSpeed);
            Fire();
            bCanFire = false; // Set the flag to false to prevent firing again immediately
            FTimerHandle FireDelayTimerHandle; // Declare the FireDelayTimerHandle
            GetWorldTimerManager().SetTimer(FireDelayTimerHandle, this, &ATurret::ResetFire, 2.0f, false); // Start a timer to reset the flag after 2 seconds
        }
        else
        {
            float CurrentAngle = FMath::Lerp(MinAngle, MaxAngle, FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds() * MoveSpeed)));
            FVector NewPosition = GetActorLocation() + FVector(FMath::Cos(FMath::DegreesToRadians(CurrentAngle)) * Radius, FMath::Sin(FMath::DegreesToRadians(CurrentAngle)) * Radius, 0.0f);
            FollowingPoint = NewPosition;
        }
    }

    FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FollowingPoint);

    // Set rotation only for the Turret Mesh
    if (TurretMesh != nullptr)
    {
        TurretMesh->SetWorldRotation(NewRotation);
    }

    if (BaseMesh != nullptr)
    {
        BaseMesh->SetMobility(EComponentMobility::Static);
        BaseMesh->SetSimulatePhysics(false);
        BaseMesh->SetEnableGravity(false);
        BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ATurret::ResetFire()
{
    bCanFire = true; // Reset the flag to allow firing again
}
