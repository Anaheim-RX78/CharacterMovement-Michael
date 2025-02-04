// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "TelecomandoBoost.generated.h"
/**
 * 
 */
UCLASS()
class CHARACTERMOVEMENT_API UTelecomandoBoost : public UInventoryItemData
{
	GENERATED_BODY()
public:

	
	void UseItem() override;
};
