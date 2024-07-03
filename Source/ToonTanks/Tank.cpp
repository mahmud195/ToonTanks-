#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
ATank::ATank()
{
    OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    OurCameraSpringArm->SetupAttachment(RootComponent);

    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

}
void ATank::BeginPlay()
{
    Super::BeginPlay();
    speed = MovementSpeed*3.0f;
    normalspeed = MovementSpeed;
    TankController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(TankController != nullptr)
    {
        FHitResult HitResult;
        bool BHitSomething = TankController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility , false , HitResult);

        if(BHitSomething == true){
            DrawDebugSphere(GetWorld() , HitResult.ImpactPoint , 10 , 15 , FColor::Red);
        } 
    FVector MouseWorldLocation = HitResult.ImpactPoint;
    RotateTurretToTarget(MouseWorldLocation);   
    }
    

}



void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::RotateRight);
    PlayerInputComponent->BindAxis("Speed", this, &ATank::Speed);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::MoveForward(float Value)
{
    FVector DeltaMovement(Value * MovementSpeed * GetWorld()->GetDeltaSeconds() , 0 , 0);
    AddActorLocalOffset(DeltaMovement , true);
}

void ATank::RotateRight(float Value)
{
    FRotator DeltaRotation(0, Value * RotationSpeed * GetWorld()->GetDeltaSeconds(), 0);
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::Speed(float Value)
{
  if (Value > 0.0f)
    MovementSpeed = speed;
  else
    MovementSpeed = normalspeed;
}

