// Fill out your copyright notice in the Description page of Project Settings.


#include "Pinko.h"

#include "DropperGameInstance.h"
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
}
// Called when the game starts or when spawned
void APinko::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);

	if (DropperInstance)
	{
		DropperInstance->MaxDepth = FMath::RandRange(0,200);
	}
	else
	{
			UE_LOG(LogTemp,Warning,TEXT("No game instance found"));
	}
}

// Called every frame
void APinko::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APinko::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APinko::SetMovementInput(const FVector2D& MovementInput)
{
	AddMovementInput(GetActorForwardVector(), MovementInput.Y);
	AddMovementInput(GetActorRightVector(), MovementInput.X);
}

void APinko::SetLookInput(const FVector2D& LookInput)
{
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

UPlayerInteractionComponent* APinko::GetInteracionComponent()
{
	return InteractionComponent;
}


