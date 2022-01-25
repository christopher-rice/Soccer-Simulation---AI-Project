#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoccerBall.h"
#include "Regions.h"
#include "SoccerTeam.h"
#include "SoccerPitch.generated.h"

UCLASS()
class FINALPROJECT_API ASoccerPitch : public AActor {
	GENERATED_BODY()

// General functions
public:
	// Constructor for ASoccerPitch
	ASoccerPitch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when a region at a certain index is needed
	ARegions* GetRegionFromIndex(int RegionIndex);

// Variables

	// Tells whether or not the game has started
	bool IsGameOn;

	// Tells whether or not the goal keeper has the ball
	bool IsBallGoalKeeper;

	// Array containing all the regions on the pitch
	TArray<AActor*> FoundRegions;

	// Number for columns of Regions on the pitch
	const int REGIONS_COLUMNS = 8;

	// Number for rows of Regions on the pitch
	const int REGIONS_ROWS = 4;

	// Pointer to the soccer ball
	ASoccerBall* ball;

	// Boolean that checks if a goal has been scored
	bool goalScored = false;

	 // Keeps track of the score for both teams
	 int redScore = 0;
	 int blueScore = 0;

	//SoccerTeam* red;
	//SoccerTeam* blue;
	 class AGoal* redGoal;
	 class AGoal* blueGoal;

// Getters and setters for variables
public:
	// Getter for IsGameOn Boolean
	FORCEINLINE bool GetIsGameOn() const { return IsGameOn; }

	// Setter for IsGameOn Boolean
	UFUNCTION()
		void SetIsGameOn(bool NewIsGameOn);

	// Getter for IsBallGoalKeeper Boolean
	FORCEINLINE bool GetIsBallGoalKeeper() const { return IsBallGoalKeeper; }

	// Setter for IsBallGoalKeeper Boolean
	UFUNCTION()
		void SetIsBallGoalKeeper(bool NewIsBallGoalKeeper);

	UFUNCTION(BlueprintCallable)
		int GetBlueScore();

	UFUNCTION(BlueprintCallable)
		int GetRedScore();
};
