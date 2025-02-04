// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "InventoryItemActor.h"
#include "Pinko.h"
#include "VisualizeTexture.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventory::AddItem(UInventoryItemData* Item, int Amount)
{
	// controlla se l'item è gia presente e in caso aumenta la quantità di questo oggetto
	if (FInventorySlot* SlotPtr = GetSlotByData(Item))
	{
		SlotPtr->Amount += Amount;
	}
	else
	{
		// se invece non è presente allora salvaimo l'item in un nuovo indirizzo vuoto dell array
		FInventorySlot Slot;
		Slot.ItemData = Item;
		Slot.Amount = Amount;
		Items.Add(Slot);
	}
	UE_LOG(LogTemp, Warning, TEXT("Inventory Item Added"));
}

void UInventory::AddItem(AInventoryItemActor* Item, int Amount)
{
	AddItem(Item->ItemData, Amount);
	// rimuove dalla scena l'item raccolto
	Item->Destroy();
}

void UInventory::DropItem(UInventoryItemData* Item, int Amount, FVector Location)
{
	// droppa un amount del Item attualmente selezionato
	for (int i = 0; i < Amount; i++)
	{
		GetWorld()->SpawnActor<AInventoryItemActor>(Item->Item, Location, FRotator::ZeroRotator);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ITEM DROPPATO! %s") , *Location.ToString()));
	}
}

void UInventory::DropItem(int Amount, FVector Location)
{
	// si occupa di controllare se l'tem selezionato è droppabile e ne gestisce la nuova quantità
	if (Items.Num() > 0 && Items.IsValidIndex(CurrentSelectedIndex))
	{
		DropItem(Items[CurrentSelectedIndex].ItemData, Amount, Location);
		Items[CurrentSelectedIndex].Amount -= Amount;
        
		if (Items[CurrentSelectedIndex].Amount <= 0)
		{
			// se amount 0 lo rimuove dall array
			Items.RemoveAt(CurrentSelectedIndex);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "NESSUN ITEM DA DROPPARE!");
	}
}

FInventorySlot* UInventory::GetSlotByData(UInventoryItemData* Item)
{
	for (FInventorySlot& Slot : Items)
	{
		if (Slot.ItemData == Item)
		{
			return &Slot;
		}
	}

	return nullptr;
}

/////funzione richiama uso del inventoryItemData
void UInventory::UseCurrentSlot()
{
	// richiama la funzione di uso item dopo essere stata chiamata essa dall imput "Use Item"
	if (Items.Num() > 0 && Items.IsValidIndex(CurrentSelectedIndex) && Items[CurrentSelectedIndex].ItemData)
	{
		// crea degli indirizzi univici per il TMap prendendosi il valore dal data set dell item
		FString ItemID = Items[CurrentSelectedIndex].ItemData->IdOggettoUsabile;

		// se l'item non è presente nella "prigione" del cooldown o la sua sentenza ha raggiunto 0 entra qui
		if (!Jail.Contains(ItemID) || Jail[ItemID] <= 0)
		{
			Items[CurrentSelectedIndex].ItemData->UseItem();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item Used!");
            
			// mette in prigione l'item per la value
			Jail.Add(ItemID, 5.0f);
		}
		else
		{
			// item ancora in prigione (cooldown)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item on cooldown!");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "No item in the selected slot!");
	}
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// scontando la sentenza in prigione del cooldown
	Jailed(DeltaTime);
	// ...
}

void UInventory::ScrollInventory(bool bForward) //richiama vero per il prossimo slot e falso per il precedente
{
	if (Items.Num() == 0) return;
	
	if (bForward)
	{
		CurrentSelectedIndex = (CurrentSelectedIndex + 1) % Items.Num();
	}
	else
	{
		CurrentSelectedIndex = (CurrentSelectedIndex - 1 + Items.Num()) % Items.Num();
	}
    
	// prende il nome del data asset dell item appena selezionato con il next e previous e lo stampa
	if (Items.IsValidIndex(CurrentSelectedIndex))
	{
		UInventoryItemData* SelectedItem = Items[CurrentSelectedIndex].ItemData;
		if (SelectedItem)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, SelectedItem->PrettyName);
		}
	}

}
void UInventory::Jailed(float DeltaTime)
{
	// prigione del cooldown
	TArray<FString> KeysToRemove;

	for (TPair<FString, float>& Pair : Jail)
	{
		Pair.Value -= DeltaTime;
		if (Pair.Value <= 0)
		{
			KeysToRemove.Add(Pair.Key);
		}
	}

	// se la sentenza è terminata il tmap viene ripulito
	for (const FString& Key : KeysToRemove)
	{
		Jail.Remove(Key);
	}
}




