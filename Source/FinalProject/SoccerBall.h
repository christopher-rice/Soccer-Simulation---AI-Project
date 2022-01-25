// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "SoccerBall.generated.h"

UCLASS()
class FINALPROJECT_API ASoccerBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoccerBall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Test function
	void Test();

	// Function for evaluating overlaps
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Some value related to the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NegDistanceTraveled;



	// Pointer to the character with the ball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ACharacter* possessor;

	// Getter for possessor
	FORCEINLINE ACharacter* GetPossessor() const { return possessor; }



	// Pointer to static mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;

	// Getter for static mesh component
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }



	// Pointer to sphere collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereCollider;

	// Getter for sphere collider
	FORCEINLINE USphereComponent* GetSphereColloider() const { return SphereCollider; }

};
