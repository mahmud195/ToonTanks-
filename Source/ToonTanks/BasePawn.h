// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RotateTurretToTarget(const FVector& TargetLocation);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* BaseMesh;

	private:
	UPROPERTY(VisibleAnywhere,Category = "Component")
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* ProjectileSpawnPoint;

	protected:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
    class UStaticMeshComponent* TurretMesh;
	
	void Fire();
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ABullet> ProjectileClass;
	
	
    virtual void RotateRight(float Value);
};
