// Fill out your copyright notice in the Description page of Project Settings.


#include "Pippo.h"

#include "Pinko.h"


void APippo::SetupInputComponent()
{
	Super::SetupInputComponent();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	Subsystem->ClearAllMappings();

	if (!InputMap)
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("CONTROLLA CHE CI SIA L'INPUIT MAP"));
	}

	Subsystem->AddMappingContext(InputMap->Context,0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(InputMap->Actions["Jump"], ETriggerEvent::Started, this, &APippo::Jump);

	EnhancedInputComponent->BindAction(InputMap->Actions["Look"], ETriggerEvent::Triggered, this, &APippo::Look);

	EnhancedInputComponent->BindAction(InputMap->Actions["Move"], ETriggerEvent::Triggered, this, &APippo::Move);

	EnhancedInputComponent->BindAction(InputMap->Actions["Interact"], ETriggerEvent::Started, this, &APippo::OnInteract);
}

void APippo::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (APinko* PinkoPawn = Cast<APinko>(InPawn)) {Pinko = PinkoPawn;}
}

void APippo::Jump(const FInputActionValue& Value)
{
	Pinko->Jump();
}

void APippo::Move(const FInputActionValue& Value)
{
	Pinko->SetMovementInput(Value.Get<FVector2d>());
}

void APippo::Look(const FInputActionValue& Value)
{
	Pinko->SetLookInput(Value.Get<FVector2d>());
}

void APippo::OnInteract(const FInputActionValue& Value)
{
	Pinko->GetInteracionComponent()->Interact();
}
