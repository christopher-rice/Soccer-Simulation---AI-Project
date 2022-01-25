// Fill out your copyright notice in the Description page of Project Settings.

#include "SoccerPitch.h"
#include "DefenderAIController.h"
#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ReturnToHomeRegionTaskNode.h"

EBTNodeResult::Type UReturnToHomeRegionTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the goalie AI controller
	ADefenderAIController* AIController = Cast<ADefenderAIController>(OwnerComponent.GetAIOwner());
	ASoccerPitch* SoccerPitch = AIController->GetSoccerPitch();

	if (AIController && SoccerPitch->goalScored) {
		// Getting the soccer pitch and the AI character
		AAICharacter* DefenderAI = AIController->GetAICharacter();

			if (SoccerPitch && DefenderAI) {
				// Gets the region at the specified index
				if (DefenderAI->GetName() == FString("RedPlayer1")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(4));
				}
				else if (DefenderAI->GetName() == FString("RedPlayer2")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(9));
				}
				else if (DefenderAI->GetName() == FString("RedPlayer3")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(13));
				}
				else if (DefenderAI->GetName() == FString("RedPlayer4")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(10));
				}
				else if (DefenderAI->GetName() == FString("RedPlayer5")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(7));
				}
				else if (DefenderAI->GetName() == FString("BluePlayer1")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(24));
				}
				else if (DefenderAI->GetName() == FString("BluePlayer2")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(21));
				}
				else if (DefenderAI->GetName() == FString("BluePlayer3")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(17));
				}
				else if (DefenderAI->GetName() == FString("BluePlayer4")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(22));
				}
				else if (DefenderAI->GetName() == FString("BluePlayer5")) {
					DefenderAI->SetHomeRegion(SoccerPitch->GetRegionFromIndex(27));
				}

				// Gets the home region for the AI Character
				ARegions* GoToRegion = DefenderAI->GetHomeRegion();
				// Moves the AI Character towards its home region
				if (GoToRegion) {
					// Gets the position of the corners of the region
					float LeftPosition = (GoToRegion->GetPosition()).X;
					float RightPosition = (GoToRegion->GetPosition()).X + GoToRegion->GetHorizontalOffset();
					float TopPosition = (GoToRegion->GetPosition()).Y;
					float BottomPosition = (GoToRegion->GetPosition()).Y + GoToRegion->GetVerticalOffset();

					// Gets a random x and y component from the vector
					float PositionX = FMath::FRandRange(LeftPosition, RightPosition);
					float PositionY = FMath::FRandRange(TopPosition, BottomPosition);

					// Moves the AI character to the position
					FVector NewPosition = FVector(PositionX, PositionY, 38.918259f);
					AIController->MoveToLocation(NewPosition);
				}
			}

		/*	SoccerPitch->goalScored = false;*/
			// The task succeeded
			return EBTNodeResult::Succeeded;
	}

	// The task failed
	return EBTNodeResult::Failed;

}
