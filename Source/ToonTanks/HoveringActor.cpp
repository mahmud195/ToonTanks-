// Fill out your copyright notice in the Description page of Project Settings.


#include "HoveringActor.h"

// Sets default values
AHoveringActor::AHoveringActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoveringActor::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	
}

void AHoveringActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector TargetLocation = IsMovingToHoverDistance ? HoverDistance : StartPosition;

    FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, HoverSpeed);

    if ((NewLocation - TargetLocation).SizeSquared() < .0001f)  
    {
        IsMovingToHoverDistance = !IsMovingToHoverDistance;

        if (IsMovingToHoverDistance)
        {
            FVector Temp = StartPosition;
            StartPosition = HoverDistance;
            HoverDistance = Temp;
        }
    }

    SetActorLocation(NewLocation);
}




