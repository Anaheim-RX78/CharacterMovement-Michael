// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemsAbilities.h"
#include "Engine/DataAsset.h"
#include "InventoryItemData.generated.h"

class AInventoryItemActor;
/**
 * 
 */
UCLASS()
class CHARACTERMOVEMENT_API UInventoryItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	// nome "in bella" dell item
	UPROPERTY(EditAnywhere,Category="ItemDetails")
	FString PrettyName;

	UPROPERTY(EditAnywhere,Category="ItemDetails")
	FString Description;
	// non implementato 
	UPROPERTY(EditAnywhere,Category="ItemDetails")
	float Weight;
	// riferimento subclass all attore del quale questo data asset fa parte
	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<AInventoryItemActor> Item;

	// ID univoco utilizzato per gestire i cooldown nella "jail" di inventory
	UPROPERTY(EditAnywhere)
	FString IdOggettoUsabile;
	

	//funzione di USO vuote in override
	UFUNCTION()
	virtual void UseItem();
};
