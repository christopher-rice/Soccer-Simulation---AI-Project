// Fill out your copyright notice in the Description page of Project Settings.


#include "SoccerTeam.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASoccerTeam::ASoccerTeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Finds the blueprint for the character
	static ConstructorHelpers::FObjectFinder<UClass> AICharacterBP(TEXT("Blueprint'/Game/Blueprints/DefenderAIBP.DefenderAIBP_C'"));
	if (AICharacterBP.Object) {
		MyAICharacterBP = (UClass*)AICharacterBP.Object;
	}
	
}

// Called when the game starts or when spawned
void ASoccerTeam::BeginPlay()
{
	Super::BeginPlay();

	// Find the soccer pitch and initialize it
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoccerPitch::StaticClass(), FoundActors);
	pitch = Cast<ASoccerPitch>(FoundActors[0]);

	// Finds the goals and initializes them
	TArray<AActor*> FoundGoals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoal::StaticClass(), FoundGoals);
	if(FoundGoals[0] && FoundGoals[1])
	{
		AGoal* goal1 = Cast<AGoal>(FoundGoals[0]);
		AGoal* goal2 = Cast<AGoal>(FoundGoals[1]);

		if (goal1->ActorHasTag(FName(TEXT("Red"))))
		{
			homeGoal = goal1;
			pitch->redGoal = homeGoal;
			goal1->heading = goal1->GetActorForwardVector();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Red Goal Forward Vector: %s"), *goal1->GetActorForwardVector().ToString()));
			opponentGoal = goal2;
			pitch->blueGoal = opponentGoal;
			goal2->heading = goal2->GetActorForwardVector();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Blue Goal Forward Vector: %s"), *goal2->GetActorForwardVector().ToString()));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GOAL ACTORS HAVE BEEN SET IN SOCCERTEAM")));
		}
		else
		{
			homeGoal = goal2;
			pitch->redGoal = homeGoal;
			opponentGoal = goal1;
			pitch->blueGoal = opponentGoal;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("GOAL ACTORS HAVE BEEN SET IN SOCCERTEAM")));
		}

		/*opponentGoal = Cast<AGoal>(FoundActors[0]);
		homeGoal = Cast<AGoal>(FoundActors[1]);*/
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("NO GOAL ACTORS FOUND IN SOCCERTEAM")));
		/*opponentGoal = Cast<AGoal>(FoundActors[1]);
		homeGoal = Cast<AGoal>(FoundActors[0]);*/
	}
	
	// Spawn in the actors of the correct team
	if (GetName() == FString("RedTeam")) {
		FVector RedPlayer1Location(-156.0f, 78.0f, 0.0f);
		FRotator RedPlayer1Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters RedPlayer1SpawnInfo;
		RedPlayer1SpawnInfo.Name = FName("RedPlayer1");
		AAICharacter* RedPlayer1 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, RedPlayer1Location, RedPlayer1Rotation, RedPlayer1SpawnInfo);
		RedPlayer1->team = this;
		RedPlayer1->playerID = 1;
		RedPlayer1->GetMesh()->SetMaterial(0, RedPlayer1->RedTeamMaterial);
		RedPlayer1->opponentGoal = pitch->blueGoal;

		FVector RedPlayer2Location(-480.0f, -122.0f, 0.0f);
		FRotator RedPlayer2Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters RedPlayer2SpawnInfo;
		RedPlayer2SpawnInfo.Name = FName("RedPlayer2");
		AAICharacter* RedPlayer2 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, RedPlayer2Location, RedPlayer2Rotation, RedPlayer2SpawnInfo);
		RedPlayer2->team = this;
		RedPlayer2->playerID = 2;
		RedPlayer2->GetMesh()->SetMaterial(0, RedPlayer2->RedTeamMaterial);
		RedPlayer2->opponentGoal = pitch->blueGoal;

		FVector RedPlayer3Location(-561.0f, -443.0f, 0.0f);
		FRotator RedPlayer3Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters RedPlayer3SpawnInfo;
		RedPlayer3SpawnInfo.Name = FName("RedPlayer3");
		AAICharacter* RedPlayer3 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, RedPlayer3Location, RedPlayer3Rotation, RedPlayer3SpawnInfo);
		RedPlayer3->team = this;
		RedPlayer3->playerID = 3;
		RedPlayer3->GetMesh()->SetMaterial(0, RedPlayer3->RedTeamMaterial);
		RedPlayer3->opponentGoal = pitch->blueGoal;

		FVector RedPlayer4Location(-480.0f, -760.0f, 0.0f);
		FRotator RedPlayer4Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters RedPlayer4SpawnInfo;
		RedPlayer4SpawnInfo.Name = FName("RedPlayer4");
		AAICharacter* RedPlayer4 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, RedPlayer4Location, RedPlayer4Rotation, RedPlayer4SpawnInfo);
		RedPlayer4->team = this;
		RedPlayer4->playerID = 4;
		RedPlayer4->GetMesh()->SetMaterial(0, RedPlayer4->RedTeamMaterial);
		RedPlayer4->opponentGoal = pitch->blueGoal;

		/*FVector RedPlayer5Location(-156.0f, -942.0f, 0.0f);
		FRotator RedPlayer5Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters RedPlayer5SpawnInfo;
		RedPlayer5SpawnInfo.Name = FName("RedPlayer5");
		AAICharacter* RedPlayer5 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, RedPlayer5Location, RedPlayer5Rotation, RedPlayer5SpawnInfo);
		RedPlayer5->team = this;
		RedPlayer5->playerID = 5;
		RedPlayer5->GetMesh()->SetMaterial(0, RedPlayer5->RedTeamMaterial);
		RedPlayer5->opponentGoal = pitch->blueGoal;*/

		// Adds players to the SoccerTeam's array of players
		players.Add(RedPlayer1);
		players.Add(RedPlayer2);
		players.Add(RedPlayer3);
		players.Add(RedPlayer4);
		//players.Add(RedPlayer5);
	}
	else if (GetName() == FString("BlueTeam")) {
		// Creates the players for the blue team
		FVector BluePlayer1Location(202.0f, 54.0f, 0.0f);
		FRotator BluePlayer1Rotation(180.0f, 0.0f, 180.0f);
		FActorSpawnParameters BluePlayer1SpawnInfo;
		BluePlayer1SpawnInfo.Name = FName("BluePlayer1");
		AAICharacter* BluePlayer1 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, BluePlayer1Location, BluePlayer1Rotation, BluePlayer1SpawnInfo);
		BluePlayer1->team = this;
		BluePlayer1->playerID = 1;
		BluePlayer1->GetMesh()->SetMaterial(0, BluePlayer1->BlueTeamMaterial);
		BluePlayer1->opponentGoal = pitch->redGoal;

		FVector BluePlayer2Location(469.0f, -122.0f, 0.0f);
		FRotator BluePlayer2Rotation(180.0f, 0.0f, 180.0f);
		FActorSpawnParameters BluePlayer2SpawnInfo;
		BluePlayer2SpawnInfo.Name = FName("BluePlayer2");
		AAICharacter* BluePlayer2 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, BluePlayer2Location, BluePlayer2Rotation, BluePlayer2SpawnInfo);
		BluePlayer2->team = this;
		BluePlayer2->playerID = 2;
		BluePlayer2->GetMesh()->SetMaterial(0, BluePlayer2->BlueTeamMaterial);
		BluePlayer2->opponentGoal = pitch->redGoal;

		FVector BluePlayer3Location(586.0f, -443.0f, 0.0f);
		FRotator BluePlayer3Rotation(180.0f, 0.0f, 180.0f);
		FActorSpawnParameters BluePlayer3SpawnInfo;
		BluePlayer3SpawnInfo.Name = FName("BluePlayer3");
		AAICharacter* BluePlayer3 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, BluePlayer3Location, BluePlayer3Rotation, BluePlayer3SpawnInfo);
		BluePlayer3->team = this;
		BluePlayer3->playerID = 3;
		BluePlayer3->GetMesh()->SetMaterial(0, BluePlayer3->BlueTeamMaterial);
		BluePlayer3->opponentGoal = pitch->redGoal;

		FVector BluePlayer4Location(469.0f, -760.0f, 0.0f);
		FRotator BluePlayer4Rotation(180.0f, 0.0f, 180.0f);
		FActorSpawnParameters BluePlayer4SpawnInfo;
		BluePlayer4SpawnInfo.Name = FName("BluePlayer4");
		AAICharacter* BluePlayer4 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, BluePlayer4Location, BluePlayer4Rotation, BluePlayer4SpawnInfo);
		BluePlayer4->team = this;
		BluePlayer4->playerID = 4;
		BluePlayer4->GetMesh()->SetMaterial(0, BluePlayer4->BlueTeamMaterial);
		BluePlayer4->opponentGoal = pitch->redGoal;

		FVector BluePlayer5Location(202.0f, -942.0f, 0.0f);
		FRotator BluePlayer5Rotation(180.0f, 0.0f, 180.0f);
		FActorSpawnParameters BluePlayer5SpawnInfo;
		BluePlayer5SpawnInfo.Name = FName("BluePlayer5");
		AAICharacter* BluePlayer5 = GetWorld()->SpawnActor<AAICharacter>(MyAICharacterBP, BluePlayer5Location, BluePlayer5Rotation, BluePlayer5SpawnInfo);
		BluePlayer5->team = this;
		BluePlayer5->playerID = 5;
		BluePlayer5->GetMesh()->SetMaterial(0, BluePlayer5->BlueTeamMaterial);
		BluePlayer5->opponentGoal = pitch->redGoal;
		
		// Adds players to the SoccerTeam's array of players
		players.Add(BluePlayer1);
		players.Add(BluePlayer2);
		players.Add(BluePlayer3);
		players.Add(BluePlayer4);
		players.Add(BluePlayer5);
	}
}

// Called every frame
void ASoccerTeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateClosestPlayerToBall();

}

void ASoccerTeam::ReturnAllFieldPlayersToHome() {

}

void ASoccerTeam::CalculateClosestPlayerToBall()
{
	double closestSoFar = 1000000;

	//Loop through each player in the team
	for (AAICharacter* player : players)
	{
		//calculate the dist. Use the squared value to avoid sqrt
		FVector playerLocation = player->GetActorLocation();
		FVector ballLocation = FVector(0, 0, 0);

		if (pitch)
		{
			ballLocation = pitch->ball->GetActorLocation();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PITCH IS NULL IN SOCCERTEAM"));
		}
		
		double distanceToBall = (playerLocation - ballLocation).Size();
		player->distanceToBall = distanceToBall;

		if (distanceToBall < closestSoFar)
		{
			closestSoFar = distanceToBall;
			playerClosestToBall = player;
		}
	}
}

