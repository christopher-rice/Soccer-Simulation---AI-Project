// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Goal.h"
#include "SoccerPitch.h"
#include "AICharacter.h"
#include "GameFramework/Actor.h"
#include "SoccerTeam.generated.h"

UCLASS()
class FINALPROJECT_API ASoccerTeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoccerTeam();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//enum team_color { Blue, Red };

	// Pointer to blueprint name for player
	TSubclassOf<class AAICharacter> MyAICharacterBP;

	// Pointers to team members
	TArray<AAICharacter*> players;

	//team_color color;
	class ASoccerPitch* pitch = nullptr;

	//Pointers to different key field players
	//ACharacter* recievingPlayer = nullptr;
	ACharacter* playerClosestToBall = nullptr;
	ACharacter* controllingPlayer = nullptr;
	//ACharacter* supportingPlayer = nullptr;

	//Pointers to goals
	class AGoal* opponentGoal;
	class AGoal* homeGoal;


public:	
	void ReturnAllFieldPlayersToHome();

	void CalculateClosestPlayerToBall();
};
