#include "TrackTaskNode.h"
#include "GoalieAIController.h"
#include "SoccerBall.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTrackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the goalie AI controller
	AGoalieAIController* AIController = Cast<AGoalieAIController>(OwnerComponent.GetAIOwner());

	if (AIController) {
		// Getting the soccer ball and goalie actor
		ASoccerBall* SoccerBall = AIController->GetSoccerBall();
		AGoalieAI* GoalieAI = AIController->GetGoalieAI();

		if (SoccerBall && GoalieAI) {
			// Gets global vector location of soccer ball and goalie
			FVector GoalieAILocation = GoalieAI->GetActorLocation();
			FVector SoccerBallLocation = SoccerBall->GetActorLocation();

			// Gets direction from goalie to soccer ball
			FVector GoalieAItoSoccerBallLocation = SoccerBallLocation - GoalieAILocation;
			GoalieAItoSoccerBallLocation.Normalize();

			// Gets the x-component of movement vector
			FVector GoalieAIMovementDirection = FVector(0, GoalieAItoSoccerBallLocation.Y, 0);

			// Blocks the goalie from moving when going past the left side of the goal
			if ((GoalieAILocation.Y <= -700) && (GoalieAItoSoccerBallLocation.Y < 0)) {
				GoalieAIMovementDirection = FVector(0, 0, 0);
			}
			// Blocks the goalie from moving when going past the right side of the goal
			else if ((GoalieAILocation.Y >= -130) && (GoalieAItoSoccerBallLocation.Y > 0)) {
				GoalieAIMovementDirection = FVector(0, 0, 0);
			}

			// Move goalie towards the soccer ball
			GoalieAI->Move(GoalieAIMovementDirection);
		}

		// The task succeeded
		return EBTNodeResult::Succeeded;
	}

	// The task failed
	return EBTNodeResult::Failed;
}

