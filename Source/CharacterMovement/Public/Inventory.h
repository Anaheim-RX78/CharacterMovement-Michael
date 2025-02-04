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

	// quantita dello stesso item presenti nello slot inventario
	UPROPERTY(EditAnywhere,category="Item")
	int Amount;

	// riferimento alla classe ItemData
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
	// Array di ITEMS di tipo FInventorySlot
	UPROPERTY(EditAnywhere, Category=Inventory)
	TArray<FInventorySlot> Items;

	// indice dell indirizzo dell array inventario che è attualmente selezionato
	UPROPERTY(visibleAnywhere, Category=Inventory)
	int CurrentSelectedIndex = 0;
	
	virtual void BeginPlay() override;

public:
	// funzione che aggiunge item
	void AddItem(UInventoryItemData* Item, int Amount);

	// altra funzione che aggiunge item ma questa è implementabile in blueprint
	// l'input di add item finisce qui
	UFUNCTION(BlueprintCallable)
	void AddItem(AInventoryItemActor* Item, int Amount);
	
	// Funzione che si occupa di effettivamente spawnare l'attore dall inventario
	void DropItem(UInventoryItemData* Item, int Amount, FVector Location);

	// funzione che controlla se l'indirizzo selezionato è un item dola l'indirizzo se amount scende a 0
	// l'input di drop item finisce qui
	void DropItem(int Amount, FVector Location);

	FInventorySlot* GetSlotByData(UInventoryItemData* Item);

	// TMap che gestisce i cooldown degli item utilizzando la loro sentenza come float e la chiave è il loro "ID univoco" settato nel data asset 
	UPROPERTY(EditAnywhere,category="Item")
	TMap<FString,float> Jail;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// funzione che prende in input gli input di previous e next slot nell inventario
	void ScrollInventory (bool bFoward);

	void Jailed(float Deltatime);
	
	//funzione che recupera l'item selezionato nell inventario e richiama la suo funzione di uso
	void UseCurrentSlot();
};
