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
	UPROPERTY(EditAnywhere,Category="ItemDetails")
	FString PrettyName;

	UPROPERTY(EditAnywhere,Category="ItemDetails")
	FString Description;
	
	UPROPERTY(EditAnywhere,Category="ItemDetails")
	float Weight;
	
	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<AInventoryItemActor> Item;

	UPROPERTY(EditAnywhere)
	FString IdOggettoUsabile;
	

	//funzione di USO vuote in override
	UFUNCTION()
	virtual void UseItem();
};
