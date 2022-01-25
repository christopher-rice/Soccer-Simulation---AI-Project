// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPitch.h"
#include "DefenderAIController.h"
#include "AICharacter.h"
#include "DribbleTaskNode.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UDribbleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the AI controller
	ADefenderAIController* AIController = Cast<ADefenderAIController>(OwnerComponent.GetAIOwner());
	// Getting the soccer pitch and the AI character
	ASoccerPitch* SoccerPitch = AIController->GetSoccerPitch();
	AAICharacter* DefenderAI = AIController->GetAICharacter();


	if (AIController && DefenderAI->isControllingPlayer()) {

		if (SoccerPitch && DefenderAI) {

			// Check if this AI is in control of the ball
			if (DefenderAI->isControllingPlayer())
			{
				// Gets global vector location of soccer ball and goal
				FVector DefenderAILocation = DefenderAI->GetActorLocation();
				//FVector OpposingGoalLocation = DefenderAI->team->opponentGoal->GetActorLocation();
				FVector OpposingGoalLocation = DefenderAI->opponentGoal->GetActorLocation();

				// Gets direction from goalie to soccer ball
				FVector KickLocation = OpposingGoalLocation - DefenderAILocation;
				KickLocation.Normalize();

				// Rotates defender to opponent goal
				FRotator directionToLookAt = UKismetMathLibrary::FindLookAtRotation(DefenderAI->heading, KickLocation);
				DefenderAI->SetActorRotation(directionToLookAt, ETeleportType::None);

				// Kicks the ball
				DefenderAI->Kick();
				//// Take the dot product to see where the player is facing
				//double dot = FVector::DotProduct(DefenderAI->team->homeGoal->heading, DefenderAI->heading);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Dot Product: %d"), dot));
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Player Forward Vector: %s"), *DefenderAI->heading.ToString()));

				////Face towards the opposing team's goal and kick the ball
				//if (dot > 0)
				//{
				//	FRotator directionToLookAt = UKismetMathLibrary::FindLookAtRotation(DefenderAI->heading, DefenderAI->team->homeGoal->heading);
				//	DefenderAI->SetActorRotation(directionToLookAt, ETeleportType::None);
				//	DefenderAI->Kick();	

				//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PLAYER MUST ROTATE"));
				//}
				//else
				//{
				//	DefenderAI->Kick();
				//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CONTROLLING PLAYER KICKED THE BALL"));
				//}

			}
			
			//TEST PRINT
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *(GoToRegion->GetPosition()).ToString()));
		}

		// The task succeeded
		return EBTNodeResult::Succeeded;
	}

	// The task failed
	return EBTNodeResult::Failed;

}


