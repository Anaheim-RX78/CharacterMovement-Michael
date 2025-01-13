// Fill out your copyright notice in the Description page of Project Settings.


#include "Pippo.h"

#include "Pinko.h"


void APippo::SetupInputComponent()
{
	Super::SetupInputComponent();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	Subsystem->ClearAllMappings();

	Subsystem->AddMappingContext(DefaultMappingContext,0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APippo::Jump);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APippo::Look);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APippo::Move);
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
