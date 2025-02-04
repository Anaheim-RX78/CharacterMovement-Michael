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
	if (FInventorySlot* SlotPtr = GetSlotByData(Item))
	{
		SlotPtr->Amount += Amount;
	}
	else
	{
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
	Item->Destroy();
}

void UInventory::DropItem(UInventoryItemData* Item, int Amount, FVector Location)
{
	for (int i = 0; i < Amount; i++)
	{
		GetWorld()->SpawnActor<AInventoryItemActor>(Item->Item, Location, FRotator::ZeroRotator);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ITEM DROPPATO! %s") , *Location.ToString()));
	}
}

void UInventory::DropItem(int Amount, FVector Location)
{
	if (Items.Num() > 0 && Items.IsValidIndex(CurrentSelectedIndex))
	{
		DropItem(Items[CurrentSelectedIndex].ItemData, Amount, Location);
		Items[CurrentSelectedIndex].Amount -= Amount;
        
		if (Items[CurrentSelectedIndex].Amount <= 0)
		{
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
	if (Items.Num() > 0 && Items.IsValidIndex(CurrentSelectedIndex) && Items[CurrentSelectedIndex].ItemData)
	{
		FString ItemID = Items[CurrentSelectedIndex].ItemData->IdOggettoUsabile;

		if (!Jail.Contains(ItemID) || Jail[ItemID] <= 0)
		{
			Items[CurrentSelectedIndex].ItemData->UseItem();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item Used!");
            
			// Apply cooldown
			Jail.Add(ItemID, 5.0f);
		}
		else
		{
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
	Jailed(DeltaTime);
	// ...
}

void UInventory::ScrollInventory(bool bForward) //richiama vero per il prossimo slot e falso per il precedente
{
	if (Items.Num() == 0) return;
    
	// Update current index
	if (bForward)
	{
		CurrentSelectedIndex = (CurrentSelectedIndex + 1) % Items.Num();
	}
	else
	{
		CurrentSelectedIndex = (CurrentSelectedIndex - 1 + Items.Num()) % Items.Num();
	}
    
	// Get selected item data
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
	TArray<FString> KeysToRemove;

	for (TPair<FString, float>& Pair : Jail)
	{
		Pair.Value -= DeltaTime;
		if (Pair.Value <= 0)
		{
			KeysToRemove.Add(Pair.Key);
		}
	}

	// Remove expired cooldowns
	for (const FString& Key : KeysToRemove)
	{
		Jail.Remove(Key);
	}
}




