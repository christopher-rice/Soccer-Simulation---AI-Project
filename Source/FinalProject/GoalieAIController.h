#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoccerBall.h"
#include "GoalieAI.h"
#include "GoalieAIController.generated.h"

UCLASS()
class FINALPROJECT_API AGoalieAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Goalie AI controller constructor
	AGoalieAIController();

	// Function called when controller possesses a pawn
	void OnPossess(APawn* InPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Pointer to the behavior tree used by the goalie AI controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTreeComponent* BehaviorTreeComponent;

	// Getter for the behavior tree component used by the goalie AI controller
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTree() const { return BehaviorTreeComponent; }

	// Pointer to the blackboard used by the goalie AI controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* BlackboardComponent;

	// Getter for the behavior tree component used by the goalie AI controller
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return BlackboardComponent; }

	// Pointer to the soccer ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASoccerBall* SoccerBall;

	// Getter for the soccer ball
	FORCEINLINE ASoccerBall* GetSoccerBall() const { return SoccerBall; }

	// Pointer to the goalie
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AGoalieAI* AIGoalie;

	// Getter for the goalie
	FORCEINLINE AGoalieAI* GetGoalieAI() const { return AIGoalie; }

	// Key for the soccer ball in blackboard
	UPROPERTY(EditDefaultsOnly)
		FName SoccerBallKey;
};
