#include "Kismet/GameplayStatics.h"
#include "SoccerPitch.h"

// Constructor for ASoccerPitch
ASoccerPitch::ASoccerPitch() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoccerPitch::BeginPlay() {
	Super::BeginPlay();
	
	// Gets array of regions in level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARegions::StaticClass(), FoundRegions);

	// Creates all arrays and puts them in array
	for (int i = 0; i < REGIONS_COLUMNS; i++) {
		for (int j = 0; j < REGIONS_ROWS; j++) {
			// Calculates the ID of the region
			int RegionID = j + (i * 4);

			// Gets a pointer to the region
			ARegions* NewRegion = Cast<ARegions>(FoundRegions[RegionID]);

			// Calculates the x and y component of the region
			float ComponentX = -2880 + (726.25 * i);
			float ComponentY = -2080 + (822.5 * j);

			// Creating a new vector position
			FVector NewPosition = FVector(ComponentX, ComponentY, 57.f);

			// Puts in ID and position
			NewRegion->SetPosition(NewPosition);
			NewRegion->SetRegionID(RegionID);			
		}
	}

	// Spawns in the red teams
	FVector RedTeamLocation(0.0f, 0.0f, 0.0f);
	FRotator RedTeamRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters RedTeamSpawnInfo;
	RedTeamSpawnInfo.Name = FName("RedTeam");
	GetWorld()->SpawnActor<ASoccerTeam>(RedTeamLocation, RedTeamRotation, RedTeamSpawnInfo);

	// Spawns in the blue teams
	FVector BlueTeamLocation(0.0f, 0.0f, 0.0f);
	FRotator BlueTeamRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters BlueTeamSpawnInfo;
	BlueTeamSpawnInfo.Name = FName("BlueTeam");
	GetWorld()->SpawnActor<ASoccerTeam>(BlueTeamLocation, BlueTeamRotation, BlueTeamSpawnInfo);

	// Set pointer to the soccer ball
	TArray<AActor*> FoundBall;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoccerBall::StaticClass(), FoundBall);
	ball = Cast<ASoccerBall>(FoundBall[0]);
}

// Called every frame
void ASoccerPitch::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (goalScored)
	{
		// Need to get blackboard and set the blackboard variable to true
	}

}

// Setter for IsGameOn Boolean
void ASoccerPitch::SetIsGameOn(bool NewIsGameOn) {
	IsGameOn = NewIsGameOn;
}

// Setter for IsBallGoalKeeper Boolean
void ASoccerPitch::SetIsBallGoalKeeper(bool NewIsBallGoalKeeper) {
	IsBallGoalKeeper = NewIsBallGoalKeeper;
}

// Called when a region at a certain index is needed
ARegions* ASoccerPitch::GetRegionFromIndex(int RegionIndex) {
	ARegions* ReturningRegion = Cast<ARegions>(FoundRegions[RegionIndex]);

	return (ReturningRegion);
}

// Returns the score of the blue team.
int ASoccerPitch::GetBlueScore() {
	return blueScore;
}

// Returns the score of the red team.
int ASoccerPitch::GetRedScore() {
	return redScore;
}
