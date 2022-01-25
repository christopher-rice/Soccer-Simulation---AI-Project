// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// APlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Sets up trigger component
	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &APlayerCharacter::Kick);
	PlayerInputComponent->BindAction("Pass", IE_Pressed, this, &APlayerCharacter::Pass);
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Called for player kick
void APlayerCharacter::Kick() {
	// Only kicks the ball if in front of player
	if (SoccerBall && IsDribble) {
		// Lets go of the soccer ball
		(SoccerBall->GetStaticMeshComponent())->SetSimulatePhysics(true);
		(SoccerBall->GetStaticMeshComponent())->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));

		// Random vertical vector for lift
		float LiftFactor = FMath::FRandRange(1.f, 2.f);
		FVector LiftVector = FVector(0, 0, 7500 * LiftFactor);

		// Creates vector for kick impulse
		FVector KickVector = LiftVector + (GetActorForwardVector() * 20000);

		// Applies impulse to soccer ball mesh
		(SoccerBall->GetStaticMeshComponent())->AddImpulseAtLocation(KickVector, SoccerBall->GetActorLocation());

		// Enables collision for soccer ball
		(SoccerBall->GetStaticMeshComponent())->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// No longer dribbling
		IsDribble = false;
	}
}

// Called for player pass 
void APlayerCharacter::Pass() {
	// Only passes the ball if in front of player
	if (SoccerBall && IsDribble) {
		// Lets go of the soccer ball
		(SoccerBall->GetStaticMeshComponent())->SetSimulatePhysics(true);
		(SoccerBall->GetStaticMeshComponent())->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));

		// Creates vector for pass impulse
		FVector PassVector = GetActorForwardVector() * 17500;

		// Applies impulse to soccer ball mesh
		(SoccerBall->GetStaticMeshComponent())->AddImpulseAtLocation(PassVector, SoccerBall->GetActorLocation());

		// Enables collision for soccer ball
		(SoccerBall->GetStaticMeshComponent())->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// No longer dribbling
		IsDribble = false;
	}
}

// Dribbles the ball
void APlayerCharacter::Dribble() {
	// Player is currently dribbling
	IsDribble = true;

	// Snaps the soccer ball to the player's socket
	(SoccerBall->GetStaticMeshComponent())->SetSimulatePhysics(false);
	(SoccerBall->GetStaticMeshComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	(SoccerBall->GetStaticMeshComponent())->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("soccerBallSocket"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
}

// When collision occurs
void APlayerCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Casts the other actor to soccer ball
	ASoccerBall* CollisionSoccerBall = Cast<ASoccerBall>(OtherActor);

	// Checks if collided with soccer ball and not currently dribbling
	if (CollisionSoccerBall && !IsDribble) {
		// Sets the soccer ball pointer for player
		SoccerBall = CollisionSoccerBall;

		// Handles soccer ball dribbling
		Dribble();

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("IMMA DRIBBLE"));
	}
}
