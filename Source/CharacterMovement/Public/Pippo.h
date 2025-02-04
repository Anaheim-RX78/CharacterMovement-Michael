// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMap.h"
#include "Pinko.h"
#include "GameFramework/PlayerController.h"
#include "Pippo.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVEMENT_API APippo : public APlayerController
{
	GENERATED_BODY()

	protected:
	// riferimento al character
		UPROPERTY(visibleAnywhere)
		APinko* Pinko;
	// riferimento alla input map
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category= Input)
		UInputMap* InputMap;

		virtual void SetupInputComponent() override;

		virtual void OnPossess(APawn* InPawn) override;

	// salto
		UFUNCTION()
		void Jump(const FInputActionValue& Value);
	// movimento wasd
		UFUNCTION()
		void Move(const FInputActionValue& Value);

	// movimento telecamera mouse
		UFUNCTION()
		void Look(const FInputActionValue& Value);

	// tasto E , generalemente per aggiungere item in questo progetto
		UFUNCTION()
		void OnInteract(const FInputActionValue& Value);

	// tasto F per usare l'abilita del item
		UFUNCTION()
		void OnUse(const FInputActionValue& Value);

	// tasto left Shift per il glider
		UFUNCTION()
		void ToggleSlowFall (const FInputActionValue& Value);

	// tasto 1 per andare allo slot precedente dell inventario
		UFUNCTION()
		void PreviousInventorySlot (const FInputActionValue& Value);

	// tasto 2 per andare allo slot successivo dell inventario
		UFUNCTION()
		void NextInventorySlot (const FInputActionValue& Value);

	// tasto G per il drop del item attualmente selezionato
		UFUNCTION()
		void DropItem (const FInputActionValue& Value);
		
};
