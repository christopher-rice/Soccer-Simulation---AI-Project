#include "DefenderAIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

ADefenderAIController::ADefenderAIController() {
	// Connecting default components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	// Defines the key name for soccer ball in blakc board
	SoccerBallKey = "SoccerBall";
}

// Called when the game starts or when spawned
void ADefenderAIController::BeginPlay()
{
	Super::BeginPlay();

	// Gets array of soccer balls in level
	TArray<AActor*> FoundSoccerBall;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoccerBall::StaticClass(), FoundSoccerBall);

	// Gives a pointer to the soccer ball in the level
	SoccerBall = Cast<ASoccerBall>(FoundSoccerBall[0]);
	BlackboardComponent->SetValueAsObject(SoccerBallKey, SoccerBall);

	// Gets array of soccer pitchs in level
	TArray<AActor*> FoundSoccerPitch;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoccerPitch::StaticClass(), FoundSoccerPitch);

	// Gives a pointer to the soccer pitch in the level
	SoccerPitch = Cast<ASoccerPitch>(FoundSoccerPitch[0]);
}

void ADefenderAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	// Casts InPawn to a defender character
	AICharacter = Cast<AAICharacter>(InPawn);

	// Starts the behavior tree if it and the blackboard exist
	if (BehaviorTreeComponent && AICharacter && (AICharacter->BehaviorTree)) {
		if ((AICharacter->BehaviorTree)->BlackboardAsset) {
			BlackboardComponent->InitializeBlackboard(*((AICharacter->BehaviorTree)->BlackboardAsset));
		}

		if (BehaviorTreeComponent) {
			BehaviorTreeComponent->StartTree(*(AICharacter->BehaviorTree));
		}
	}
}