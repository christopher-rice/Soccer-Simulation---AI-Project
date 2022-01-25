// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalieAI.h"

// Sets default values
AGoalieAI::AGoalieAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up trigger component
	TriggerComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerComponent"));
	TriggerComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AGoalieAI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGoalieAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(MovementDirection);

	TArray<AActor*> OverlappingActors;
	TriggerComponent->GetOverlappingActors(OverlappingActors);
	for (AActor* actor : OverlappingActors) {
		if (actor->IsA(ASoccerBall::StaticClass())) {
			IsOverlapSoccerBall = true;
		}
		else {
			IsOverlapSoccerBall = false;
		}
	}
}

// Called to bind functionality to input
void AGoalieAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when moving goalie
void AGoalieAI::Move(FVector& MoveDirection) {
	MovementDirection = MoveDirection;
}