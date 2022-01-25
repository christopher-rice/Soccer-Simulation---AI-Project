#include "CatchTaskNode.h"
#include "GoalieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCatchTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the goalie AI controller
	AGoalieAIController* AIController = Cast<AGoalieAIController>(OwnerComponent.GetAIOwner());

	if (AIController) {
		// Getting the soccer ball and goalie actor
		ASoccerBall* SoccerBall = AIController->GetSoccerBall();
		AGoalieAI* GoalieAI = AIController->GetGoalieAI();

		if (SoccerBall && GoalieAI) {
			if (GoalieAI->IsOverlapSoccerBall) {
				int32 CatchOdds = FMath::RandRange(1, 100);

				// The goalie catches the ball
				if (CatchOdds <= 33) {
					FTimerHandle TimerHandle;
					FTimerDelegate TimerDel;

					(SoccerBall->GetStaticMeshComponent())->SetSimulatePhysics(false);
					(SoccerBall->GetStaticMeshComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
					(SoccerBall->GetStaticMeshComponent())->AttachToComponent((GoalieAI->GetMesh()), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GoalieSocket"));

					(SoccerBall->GetStaticMeshComponent())->SetSimulatePhysics(true);
					(SoccerBall->GetStaticMeshComponent())->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));

					(SoccerBall->GetStaticMeshComponent())->AddImpulseAtLocation(FVector(0, 10000, 10000), SoccerBall->GetActorLocation());

					TimerDel.BindUFunction(this, FName("EnableSoccerBallCollisions"), SoccerBall);
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.3, false);
				}
				// The goalie kicks the ball
				else if (CatchOdds <= 66) {
					float RandomYImpulse = FMath::FRandRange(1.f, 2.f);
					float RandomZImpulse = FMath::FRandRange(1.f, 2.f);

					(SoccerBall->GetStaticMeshComponent())->AddImpulseAtLocation(FVector(0, (10000 * RandomYImpulse), (10000 * RandomZImpulse)), SoccerBall->GetActorLocation());
				}
			}
		}
	}

	// The task failed
	return EBTNodeResult::Failed;
}

void UCatchTaskNode::EnableSoccerBallCollisions(ASoccerBall* SoccerBall) {
	(SoccerBall->GetStaticMeshComponent())->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}