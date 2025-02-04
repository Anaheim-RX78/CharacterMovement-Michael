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
		UPROPERTY(visibleAnywhere)
		APinko* Pinko;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category= Input)
		UInputMap* InputMap;

		virtual void SetupInputComponent() override;

		virtual void OnPossess(APawn* InPawn) override;

		UFUNCTION()
		void Jump(const FInputActionValue& Value);
	
		UFUNCTION()
		void Move(const FInputActionValue& Value);

		UFUNCTION()
		void Look(const FInputActionValue& Value);

		UFUNCTION()
		void OnInteract(const FInputActionValue& Value);

		UFUNCTION()
		void OnUse(const FInputActionValue& Value);
	//on use
		UFUNCTION()
		void ToggleSlowFall (const FInputActionValue& Value);

		UFUNCTION()
		void PreviousInventorySlot (const FInputActionValue& Value);

		UFUNCTION()
		void NextInventorySlot (const FInputActionValue& Value);

		UFUNCTION()
		void DropItem (const FInputActionValue& Value);
		
};
