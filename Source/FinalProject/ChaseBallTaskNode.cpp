// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPitch.h"
#include "DefenderAIController.h"
#include "AICharacter.h"
#include "ChaseBallTaskNode.h"

EBTNodeResult::Type UChaseBallTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the AI controller
	ADefenderAIController* AIController = Cast<ADefenderAIController>(OwnerComponent.GetAIOwner());

	if (AIController) {
		// Getting the soccer pitch and the AI character
		ASoccerPitch* SoccerPitch = AIController->GetSoccerPitch();
		AAICharacter* DefenderAI = AIController->GetAICharacter();

		if (SoccerPitch && DefenderAI) {
		
			// Check if this AI is the closest Team Member to the Ball, if it is, pursue the ball
			if (DefenderAI->isClosestTeamMemberToBall())
			{
				AIController->MoveToLocation(DefenderAI->team->pitch->ball->GetActorLocation());
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Closest Player is: %d"), DefenderAI->playerID));
			}

			//TEST PRINT
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *(GoToRegion->GetPosition()).ToString()));
		}

		// The task succeeded
		return EBTNodeResult::Failed;
	}

	// The task failed
	return EBTNodeResult::Succeeded;

}

