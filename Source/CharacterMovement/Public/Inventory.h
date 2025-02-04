// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

USTRUCT()
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,category="Item")
	int Amount;

	UPROPERTY(EditAnywhere,category="Item")
	UInventoryItemData* ItemData;
};

UCLASS( ClassGroup=(InventorySystem), meta=(BlueprintSpawnableComponent) )
class CHARACTERMOVEMENT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

protected:
	UPROPERTY(EditAnywhere, Category=Inventory)
	TArray<FInventorySlot> Items;

	UPROPERTY(visibleAnywhere, Category=Inventory)
	int CurrentSelectedIndex = 0;
	
	virtual void BeginPlay() override;

public:
	void AddItem(UInventoryItemData* Item, int Amount);

	UFUNCTION(BlueprintCallable)
	void AddItem(AInventoryItemActor* Item, int Amount);

	void DropItem(UInventoryItemData* Item, int Amount, FVector Location);

	void DropItem(int Amount, FVector Location);

	FInventorySlot* GetSlotByData(UInventoryItemData* Item);

	UPROPERTY(EditAnywhere,category="Item")
	TMap<FString,float> Jail;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ScrollInventory (bool bFoward);

	void Jailed(float Deltatime);
	
	//funzione che recupera l'item selezionato nell inventario e richiama la suo funzione di uso
	void UseCurrentSlot();
};
