#include "GoalieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AGoalieAIController::AGoalieAIController() {
	// Creates subobjects for the behavior tree and blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	// Defines the key name for soccer ball in blakc board
	SoccerBallKey = "SoccerBall";
}

// Called when the game starts or when spawned
void AGoalieAIController::BeginPlay()
{
	Super::BeginPlay();

	// Defines the soccer ball class
	TSubclassOf<ASoccerBall> ClassToFind;
	ClassToFind = ASoccerBall::StaticClass();

	// Gets array of soccer balls in level
	TArray<AActor*> FoundSoccerBall;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundSoccerBall);

	// Gives a pointer to the soccer ball in the level
	SoccerBall = Cast<ASoccerBall>(FoundSoccerBall[0]);
	BlackboardComponent->SetValueAsObject(SoccerBallKey, SoccerBall);
}

void AGoalieAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	// Casts InPawn to a goalie character
	AIGoalie = Cast<AGoalieAI>(InPawn);

	// Starts the behavior tree if it and the blackboard exist
	if (BehaviorTreeComponent && AIGoalie && (AIGoalie->BehaviorTree)) {
		if ((AIGoalie->BehaviorTree)->BlackboardAsset) {
			BlackboardComponent->InitializeBlackboard(*((AIGoalie->BehaviorTree)->BlackboardAsset));
		}

		if (BehaviorTreeComponent) {
			BehaviorTreeComponent->StartTree(*(AIGoalie->BehaviorTree));
		}
	}
}