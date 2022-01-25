#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Regions.generated.h"

UCLASS()
class FINALPROJECT_API ARegions : public AActor
{
	GENERATED_BODY()

// Functions
public:
	// Constructor for Region
	ARegions();

// Variables
protected:
	// Positional vector for top left corner of Region
	FVector Position = FVector(0.f, 0.f, 57.f);

	// Horizontal offset for top left corner
	const float HORIZONTAL_OFFSET = 726.25;

	// Vertical offset for top left corner
	const float VERTICAL_OFFSET = 822.5;

	// ID for region
	int RegionID = 0;


// Getters and setters for variables
public:
	// Getter for Position
	FORCEINLINE FVector GetPosition() const { return Position; }

	// Setter for Position
	UFUNCTION()
		void SetPosition(FVector NewPosition);

	// Getter for horizontal offset
	FORCEINLINE float GetHorizontalOffset() { return HORIZONTAL_OFFSET; }

	// Getter for vertical offset
	FORCEINLINE float GetVerticalOffset() { return VERTICAL_OFFSET; }

	// Getter for RegionID
	FORCEINLINE int GetRegionID() const { return RegionID; }

	// Setter for RegionID
	UFUNCTION()
		void SetRegionID(int NewRegionID);

};