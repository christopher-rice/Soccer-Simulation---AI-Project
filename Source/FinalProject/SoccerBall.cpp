// Fill out your copyright notice in the Description page of Project Settings.


#include "SoccerBall.h"

// Sets default values
ASoccerBall::ASoccerBall() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets defaults for components
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));

	// Sets default for values
	NegDistanceTraveled = 0.0f;
}

void ASoccerBall::Test() {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Test passed");
}

// Called when the game starts or when spawned
void ASoccerBall::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASoccerBall::OnOverlapBegin);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoccerBall::OnOverlapBegin);
}

// Called every frame
void ASoccerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (possessor) {
		NegDistanceTraveled += (possessor->GetVelocity().Size()) * -0.015f;

		SetActorLocationAndRotation((possessor->GetActorLocation()) * (possessor->GetActorForwardVector()) * 90.0f + FVector(0.0f, 0.0f, -60.f), FRotator(1, possessor->GetActorRotation().Yaw, 0.0f));

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SetActorLocation"));
	}

}

void ASoccerBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	if (ACharacter* character = Cast<ACharacter>(OtherActor)) {
		possessor = character;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Possesor has been set"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Possesor has NOT been set"));
	}
	*/
}

