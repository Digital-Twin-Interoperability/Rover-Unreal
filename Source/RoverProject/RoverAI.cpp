#include "RoverAI.h"
#include "GameFramework/Actor.h"

ARoverAI::ARoverAI()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentState = ERoverState::MovingForward;
    TimeSinceLastStateChange = 0.0f;
    TurnDuration = 4.0f;
    MoveDuration = 5.0f; 
}

void ARoverAI::BeginPlay()
{
    Super::BeginPlay();
}

void ARoverAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastStateChange += DeltaTime;

    switch (CurrentState)
    {
    case ERoverState::MovingForward:
        MoveForward(DeltaTime);
        if (TimeSinceLastStateChange >= MoveDuration)
        {
            CurrentState = ERoverState::Turn;
            TimeSinceLastStateChange = 0.0f;
        }
        break;

    case ERoverState::Turn:
        Turn(DeltaTime);
        if (TimeSinceLastStateChange >= TurnDuration)
        {
            CurrentState = ERoverState::MovingForward;
            TimeSinceLastStateChange = 0.0f;
        }
        break;
    }
}

void ARoverAI::MoveForward(float DeltaTime)
{
    float DesiredSpeed = 500.0f;

    float CurrentSpeed = GetVehicleMovementComponent()->GetForwardSpeed();

    float SpeedDifference = DesiredSpeed - CurrentSpeed;

    float ThrottleAdjustment = FMath::Clamp(SpeedDifference * 0.1f, -1.0f, 1.0f); 

  
    GetVehicleMovementComponent()->SetThrottleInput(ThrottleAdjustment);
}

void ARoverAI::Turn(float DeltaTime)
{
    GetVehicleMovementComponent()->SetYawInput(1.0f);
}
