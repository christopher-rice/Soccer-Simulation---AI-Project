// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up trigger component
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent"));
	TriggerComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

	heading = GetActorForwardVector();
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);

	// Gets array of soccer pitchs in level
	TArray<AActor*> FoundSoccerPitch;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoccerPitch::StaticClass(), FoundSoccerPitch);

	// Gives a pointer to the soccer pitch in the level
	pitch = Cast<ASoccerPitch>(FoundSoccerPitch[0]);
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when defender overlaps with another actor
void AGoal::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Casts the other actor to soccer ball
	ASoccerBall* CollisionSoccerBall = Cast<ASoccerBall>(OtherActor);

	// Checks if collided with soccer ball
	if (CollisionSoccerBall) {

		if (pitch)
		{
			if (this->ActorHasTag((FName(TEXT("Red")))))
            {
                pitch->blueScore++;
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Red Team Scored"));
            }
            else if (this->ActorHasTag((FName(TEXT("Blue")))))
            {
                pitch->redScore++;
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("blue Team Scored"));
            }
			//Reset the soccer ball back to the center
			pitch->goalScored = true;
			FVector center = FVector(24.830444, -505.644287, -15.551453);
			CollisionSoccerBall->GetStaticMeshComponent()->SetPhysicsLinearVelocity(FVector::ZeroVector);
			CollisionSoccerBall->SetActorLocation(center);
		/*	CollisionSoccerBall->GetStaticMeshComponent()->SetPhysicsLinearVelocity(FVector::ZeroVector);
			CollisionSoccerBall->GetStaticMeshComponent()->SetSimulatePhysics(false);
			CollisionSoccerBall->GetStaticMeshComponent()->SetSimulatePhysics(true);*/
			

			//TEST
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("GOAL SCORED"));
			
		}
		else
		{
			//TEST
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PITCH IS NULL IN GOAL"));
		}
		

		
	}
}

