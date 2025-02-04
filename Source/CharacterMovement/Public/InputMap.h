// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/DataAsset.h"
#include "InputMap.generated.h"

/**
 * 
 */


UCLASS(Blueprintable)
class CHARACTERMOVEMENT_API UInputMap : public UDataAsset
{
	GENERATED_BODY()

public:
	// costruttore per il mapping context e le imput actions
	UPROPERTY(editAnywhere, Category = Input)
	UInputMappingContext* Context;

	UPROPERTY(EditAnywhere,category = Input)
	TMap<FString, UInputAction*> Actions;
};
