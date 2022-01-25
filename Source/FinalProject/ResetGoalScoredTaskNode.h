// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ResetGoalScoredTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UResetGoalScoredTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory);
	
};
