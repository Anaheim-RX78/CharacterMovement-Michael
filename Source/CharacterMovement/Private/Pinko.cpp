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
	GliderMesh->SetupAttachment(RootComponent); 
	GliderMesh->SetVisibility(false); // nascosto di default

	
}
// Called when the game starts or when spawned
void APinko::BeginPlay()
{
	Super::BeginPlay();
	// inizializza lo score facendo un cast alla game instance e chiamando start level
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);

	if (DropperInstance)
	{
		DropperInstance->StartLevel(10000);
		// il primo checkpoint è il punto di spawn in play
		DropperInstance->CheckpointLocation = GetActorLocation();
	}
	else
	{
			UE_LOG(LogTemp,Warning,TEXT("No game instance found"));
	}
	// controllo ridondante per avere la gravità e l'air control desiderato di defualt
	GetCharacterMovement()->GravityScale = FallingSpeedGravity;
	GetCharacterMovement()->AirControl = ReducedAirControl;
}

// Called every frame
void APinko::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float FallSpeed = GetVelocity().Z;

	// funzione nativa di unreal che controlla se Z è negativa
	if (GetCharacterMovement()->IsFalling())
	{
		// spedometro?
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Red,FString::Printf(TEXT("Falling Speed: %.2f"), FallSpeed));
		}
		UE_LOG(LogTemp, Warning, TEXT("Falling Speed: %.2f"), FallSpeed);
	}

	if (GEngine)
	{
		// mostra la gravity scale e l'air control attuale
		FString DebugMessage = FString::Printf(TEXT("Gravity: %.2f | Air Control: %.2f"),GetCharacterMovement()->GravityScale,GetCharacterMovement()->AirControl);
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Cyan, DebugMessage);
	}
	// cast alla game instance per accedere allo score update
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);
	if (DropperInstance)
	{
		DropperInstance->UpdateScore(DeltaTime);
	}
}


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

// toggle del glider e gravità/air control
void APinko::ToggleSlowFall()
{
	
	if (!GetCharacterMovement()->IsFalling()) 
	{
		// stops the palyer from changing gravity on foot
		return;
	}

	if (IsSlowFalling)
	{
		// se siamo in slow fall ci dobbiamo uscire
		GetCharacterMovement()->GravityScale = FallingSpeedGravity;
		GetCharacterMovement()->AirControl = ReducedAirControl;
		IsSlowFalling = false;
		GliderMesh->SetVisibility(false);
	}
	else
	{
		// e viceversa
		GetCharacterMovement()->GravityScale = FallingSpeedReducedGravity;
		GetCharacterMovement()->AirControl = AirControl;

		// direzione della spinta verticale per rallentare
		FVector UpdraftDirection = FVector(0, 0, 1);
		FVector UpdraftForceVec = UpdraftDirection * UpdraftForce;
		GliderMesh->SetVisibility(true);
        
		// spinta verticale
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


// funzione nativa del character che controlal un hit con una superfice sotto il character
void APinko::Landed(const FHitResult& Hit)
{
	// resetta tutto al default "a piedi" quando si atterra
	Super::Landed(Hit);
	IsSlowFalling = true;
	ToggleSlowFall();
}
UPlayerInteractionComponent* APinko::GetInteracionComponent()
{
	return InteractionComponent;
}


