// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoccerBall.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GoalieAI.generated.h"

UCLASS()
class FINALPROJECT_API AGoalieAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGoalieAI();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to move the goalie
	void Move(FVector& MoveDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Pointer to the trigger component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCapsuleComponent* TriggerComponent;

	// Getter for the goalie's trigger component
	FORCEINLINE class UCapsuleComponent* GetTriggerComponent() const { return TriggerComponent; }

	// Pointer to the behavior tree attached to goalie AI
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

	// Getter for the goalie AI's behavior tree
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	// Direction of movement
	UPROPERTY(EditAnywhere)
		FVector MovementDirection = FVector(0, 0, 0);

	// Tells if actor is overlapping
	UPROPERTY(EditAnywhere)
		bool IsOverlapSoccerBall = false;

};
