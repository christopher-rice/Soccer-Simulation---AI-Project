// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetGoalScoredTaskNode.h"
#include "SoccerPitch.h"
#include "DefenderAIController.h"
#include "AICharacter.h"
#include "ReturnToHomeRegionTaskNode.h"

EBTNodeResult::Type UResetGoalScoredTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {
	// Getting the goalie AI controller
	ADefenderAIController* AIController = Cast<ADefenderAIController>(OwnerComponent.GetAIOwner());
	ASoccerPitch* SoccerPitch = AIController->GetSoccerPitch();

	if (AIController && SoccerPitch->goalScored){


		SoccerPitch->goalScored = false;
		// The task succeeded
		return EBTNodeResult::Succeeded;
	}
	// The task failed
	return EBTNodeResult::Failed;

}

