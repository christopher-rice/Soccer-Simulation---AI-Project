#pragma once

#include "CoreMinimal.h"
#include "SoccerTeam.h"
#include "SoccerBall.h"
#include "Regions.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/SphereComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class FINALPROJECT_API AAICharacter : public ACharacter {
	GENERATED_BODY()

// General functions
public:
	// Sets default values for this character's properties
	AAICharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// A pointer to this player's team
	class ASoccerTeam* team;

	// Pointers to goals
	class AGoal* opponentGoal;
	class AGoal* homeGoal;

	// Stores player's ID
	int playerID = -1;

	//the region that this player is assigned to.
	int homeRegion = -1;

	// The distance to the ball
	double distanceToBall;

	// Direction the player is facing
	FVector heading;

	// Pointer to red team material
	UPROPERTY(EditAnywhere)
		class UMaterial* RedTeamMaterial;

	// Pointer to blue team material
	UPROPERTY(EditAnywhere)
		class UMaterial* BlueTeamMaterial;

	// Returns if this AI character is the closest team member to the ball
	UFUNCTION()
		bool isClosestTeamMemberToBall();
	// Returns if this AI is dribbling the ball (Later this should also be set if they are recieving the ball)
	UFUNCTION()
		bool isControllingPlayer();

	// When collision occurs
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called for player kick
	UFUNCTION()
		void Kick();

	// Called for player pass 
	UFUNCTION()
		void Pass();

	// Called when the play needs to dribble
	UFUNCTION()
		void Dribble();

	// Called when the player needs to seek
	UFUNCTION()
		FVector Seek(FVector targetPos);

	// Pointer to the behavior tree
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

	// Pointer to the trigger component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* TriggerComponent;

	// Pointer to the soccer ball that the player overlaps with
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASoccerBall* SoccerBall;

	// Pointer to the AI's home region
	UPROPERTY(EditAnywhere)
		ARegions* HomeRegion;

	// Tells if dribbling
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDribble = false;

// Getters and setters for variables
public:	
	// Getter for the behavior tree
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	// Getter for the goalie's trigger component
	FORCEINLINE class USphereComponent* GetTriggerComponent() const { return TriggerComponent; }

	// Getter for the goalie's trigger component
	FORCEINLINE class ASoccerBall* GetSoccerBall() const { return SoccerBall; }

	// Getter for the home region
	FORCEINLINE class ARegions* GetHomeRegion() const { return HomeRegion; }

	// Setter for the home region
	UFUNCTION()
		void SetHomeRegion(ARegions* NewHomeRegion);
};
