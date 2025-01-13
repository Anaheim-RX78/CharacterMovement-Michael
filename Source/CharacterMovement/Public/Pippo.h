// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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
	
		UPROPERTY(editAnywhere, BlueprintReadWrite, category= Input)
		UInputMappingContext* DefaultMappingContext;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, category= Input)
		UInputAction* JumpAction;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category= Input)
		UInputAction* MoveAction;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category= Input)
		UInputAction* LookAction;

		virtual void SetupInputComponent() override;

		virtual void OnPossess(APawn* InPawn) override;

		UFUNCTION()
		void Jump(const FInputActionValue& Value);
	
		UFUNCTION()
		void Move(const FInputActionValue& Value);

		UFUNCTION()
		void Look(const FInputActionValue& Value);
};
