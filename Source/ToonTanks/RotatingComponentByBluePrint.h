// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatingComponentByBluePrint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API URotatingComponentByBluePrint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatingComponentByBluePrint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
UFUNCTION(BlueprintCallable)
void RotateMesh(UStaticMeshComponent* MeshComponent, float MinAngle, float MaxAngle, float LerpSpeed,float DeltaTime);
UPROPERTY(EditAnywhere, Category = "Rotation")
float RotationSpeed = 1.0f;

		
};
