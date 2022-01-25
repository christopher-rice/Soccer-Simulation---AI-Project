// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoccerBall.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CatchTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UCatchTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory);

	UFUNCTION()
		void EnableSoccerBallCollisions(ASoccerBall* SoccerBall);
};
