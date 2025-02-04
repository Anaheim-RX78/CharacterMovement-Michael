// Fill out your copyright notice in the Description page of Project Settings.


#include "Pinko.h"

#include "DropperGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APinko::APinko()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength=500.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);

	Inventory=CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("Interaction"));
	InteractionComponent->SetupAttachment(Camera);

	GliderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GliderMesh"));
	GliderMesh->SetupAttachment(RootComponent); // Attach to character
	GliderMesh->SetVisibility(false); // Hide it by default

	
}
// Called when the game starts or when spawned
void APinko::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);

	if (DropperInstance)
	{
		DropperInstance->StartLevel(10000);
		DropperInstance->CheckpointLocation = GetActorLocation();
	}
	else
	{
			UE_LOG(LogTemp,Warning,TEXT("No game instance found"));
	}
	///GESTIONE VELOCITA DI CADUTA
	GetCharacterMovement()->GravityScale = FallingSpeedGravity;
	GetCharacterMovement()->AirControl = ReducedAirControl;
}

// Called every frame
void APinko::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float FallSpeed = GetVelocity().Z;

	// Check if the character is falling (negative Z velocity)
	if (GetCharacterMovement()->IsFalling())
	{
		// Print the fall speed on screen
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, // Message ID (-1 = always add new)
				0.1f, // Duration (how long the message stays on screen)
				FColor::Red, // Color of text
				FString::Printf(TEXT("Falling Speed: %.2f"), FallSpeed) // Formatted string
			);
		}

		// Print the fall speed in the Output Log
		UE_LOG(LogTemp, Warning, TEXT("Falling Speed: %.2f"), FallSpeed);
	}

	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Gravity: %.2f | Air Control: %.2f"),
											   GetCharacterMovement()->GravityScale,
											   GetCharacterMovement()->AirControl);
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Cyan, DebugMessage);
	}
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);
	if (DropperInstance)
	{
		DropperInstance->UpdateScore(DeltaTime);
	}
}

// Called to bind functionality to input
void APinko::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APinko::SetMovementInput(const FVector2D& MovementInput)
{
	AddMovementInput(FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::Y), MovementInput.X);
	AddMovementInput(FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X), MovementInput.Y);
}

void APinko::SetLookInput(const FVector2D& LookInput)
{
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void APinko::ToggleSlowFall()
{
	// Check if the character is on the ground, do nothing if on the ground
	if (!GetCharacterMovement()->IsFalling()) 
	{
		// Character is on the ground, return without applying slow fall
		return;
	}

	if (IsSlowFalling)
	{
		// Reset to normal fall speed and air control
		GetCharacterMovement()->GravityScale = FallingSpeedGravity;
		GetCharacterMovement()->AirControl = ReducedAirControl;
		IsSlowFalling = false;
		GliderMesh->SetVisibility(false);
	}
	else
	{
		// Apply slow fall settings and reduced air control
		GetCharacterMovement()->GravityScale = FallingSpeedReducedGravity;
		GetCharacterMovement()->AirControl = AirControl;

		// Apply Updraft force (only when in the air)
		FVector UpdraftDirection = FVector(0, 0, 1);
		FVector UpdraftForceVec = UpdraftDirection * UpdraftForce;
		GliderMesh->SetVisibility(true);
        
		// Launch with the updraft force (but only when in the air)
		if (GetCharacterMovement()->IsFalling())
		{
			GetCharacterMovement()->Launch(FVector(0, 0, UpdraftForceVec.Z));
		}

		IsSlowFalling = true;
	}
}

void APinko::ForwardBoost()
{
	/*
	FVector BoostDir = FVector(1, 0, 0);
	FVector BoostPower = BoostDir * 1000;
	GetCharacterMovement()->Launch(FVector(BoostPower.Z, 0, 0));
	*/
}


void APinko::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	IsSlowFalling = true;
	ToggleSlowFall();
}
UPlayerInteractionComponent* APinko::GetInteracionComponent()
{
	return InteractionComponent;
}


