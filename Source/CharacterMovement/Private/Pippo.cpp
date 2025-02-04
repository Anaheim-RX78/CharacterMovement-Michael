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

	EnhancedInputComponent->BindAction(InputMap->Actions["Use Item"], ETriggerEvent::Started, this, &APippo::OnUse);

	EnhancedInputComponent->BindAction(InputMap->Actions["Slow Fall"], ETriggerEvent::Started, this, &APippo::ToggleSlowFall);

	EnhancedInputComponent->BindAction(InputMap->Actions["Previous Slot"], ETriggerEvent::Started, this, &APippo::PreviousInventorySlot);

	EnhancedInputComponent->BindAction(InputMap->Actions["Next Slot"], ETriggerEvent::Started, this, &APippo::NextInventorySlot);

	EnhancedInputComponent->BindAction(InputMap->Actions["Drop Item"], ETriggerEvent::Started, this, &APippo::DropItem);
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
//on use richiama inventory->use
void APippo::OnUse(const FInputActionValue& Value)
{
	Pinko->Inventory->UseCurrentSlot();
}

void APippo::ToggleSlowFall(const FInputActionValue& Value)
{
	Pinko->ToggleSlowFall();
}

void APippo::PreviousInventorySlot(const FInputActionValue& Value)
{
	Pinko->Inventory->ScrollInventory(false);
}

void APippo::NextInventorySlot(const FInputActionValue& Value)
{
	Pinko->Inventory->ScrollInventory(true);
}

void APippo::DropItem(const FInputActionValue& Value)
{
    Pinko->Inventory->DropItem(1, Pinko->GetActorLocation());
}


