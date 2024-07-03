// CPP file for HoveringComponent
#include "HoveringComponent.h"

// Sets default values for this component's properties
UHoveringComponent::UHoveringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHoveringComponent::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetOwner()->GetActorLocation();
}

// Called every frame
void UHoveringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = IsMovingToHoverDistance ? HoverDistance : StartPosition;

	FVector NewLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), TargetLocation, DeltaTime, HoverSpeed);

	if ((NewLocation - TargetLocation).SizeSquared() < 0.0001f)  
	{
		IsMovingToHoverDistance = !IsMovingToHoverDistance;

		if (IsMovingToHoverDistance)
		{
			FVector Temp = StartPosition;
			StartPosition = HoverDistance;
			HoverDistance = Temp;
		}
	}

	GetOwner()->SetActorLocation(NewLocation);
}
