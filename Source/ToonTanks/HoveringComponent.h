// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoveringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHoveringComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoveringComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, Category = "Hovering")
	float HoverSpeed = 100.0f;

	// Distance to hover
	UPROPERTY(EditAnywhere, Category = "Hovering")
	FVector HoverDistance = FVector(0, 0, 0);

	FVector StartPosition = FVector(0, 0, 0);

	bool IsMovingToHoverDistance;	
};
