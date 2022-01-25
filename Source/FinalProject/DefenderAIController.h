#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoccerBall.h"
#include "SoccerPitch.h"
#include "AICharacter.h"
#include "DefenderAIController.generated.h"

UCLASS()
class FINALPROJECT_API ADefenderAIController : public AAIController {
	GENERATED_BODY()

// General functions
public:
	// Constructor for the defender AI controller
	ADefenderAIController();

	// Called when controller possesses defender
	virtual void OnPossess(APawn* InPawn) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Variables
protected:
	// Pointer to the behavior tree component
	UPROPERTY()
		class UBehaviorTreeComponent* BehaviorTreeComponent;

	// Pointer to the blackboard component
	UPROPERTY(BlueprintReadWrite)
		class UBlackboardComponent* BlackboardComponent;

	// Pointer to the soccer ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASoccerBall* SoccerBall;

	// Pointer to the goalie
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAICharacter* AICharacter;

	// Name for point in blackboard
	UPROPERTY(EditDefaultsOnly)
		FName SoccerBallKey;

	// Pointer to the soccer pitch
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASoccerPitch* SoccerPitch;

	// Name for point in blackboard
	UPROPERTY(EditDefaultsOnly)
		FName SoccerPitchKey;

// Getters and setters for variables
public:
	// Getter for the behavior tree component
	FORCEINLINE class UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }

	// Getter for the blackboard component
	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }

	// Getter for the soccer ball
	FORCEINLINE ASoccerBall* GetSoccerBall() const { return SoccerBall; }

	// Getter for the goalie
	FORCEINLINE AAICharacter* GetAICharacter() const { return AICharacter; }

	// Getter for the soccer pitch
	FORCEINLINE ASoccerPitch* GetSoccerPitch() const { return SoccerPitch; }
};
