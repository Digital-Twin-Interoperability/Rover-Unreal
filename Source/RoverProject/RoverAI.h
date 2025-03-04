#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleMovementComponent.h"
#include "WheeledVehiclePawn.h"
#include "RoverAI.generated.h"

UCLASS()
class ROVERPROJECT_API ARoverAI : public AWheeledVehiclePawn
{
    GENERATED_BODY()

public:
    ARoverAI();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    void MoveForward(float DeltaTime);
	void Turn(float DeltaTime);
	enum class ERoverState
	{
		MovingForward,
		Turn
	};

	ERoverState CurrentState;
	float TimeSinceLastStateChange;
	float TurnDuration;
	float MoveDuration;
};
