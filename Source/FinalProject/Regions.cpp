// Fill out your copyright notice in the Description page of Project Settings.


#include "Regions.h"

// Sets default values
ARegions::ARegions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Setter for Position
void ARegions::SetPosition(FVector NewPosition) {
	Position = NewPosition;
}

// Setter for RegionID
void ARegions::SetRegionID(int NewRegionID) {
	RegionID = NewRegionID;
}

