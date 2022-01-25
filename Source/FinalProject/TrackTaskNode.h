// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TrackTaskNode.generated.h"

/**
 * This task node will define the behavior for the goalie tracking the ball.
 * The goalie will follow the soccer ball along the 2D plane of the goal.
 */
UCLASS()
class FINALPROJECT_API UTrackTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory);
};
