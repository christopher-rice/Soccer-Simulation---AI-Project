// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoccerBall.h"
#include "SoccerPitch.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class FINALPROJECT_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	FVector heading;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ASoccerPitch* pitch;

	// When collision occurs
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Pointer to the trigger component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* TriggerComponent;

};
