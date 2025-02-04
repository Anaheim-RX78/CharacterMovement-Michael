// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemsAbilities.h"
#include "GameFramework/Actor.h"
#include "InventoryItemActor.generated.h"


UCLASS()
class CHARACTERMOVEMENT_API AInventoryItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemActor();

	UPROPERTY(EditAnywhere, Category = Abilities)
	UItemsAbilities* AbilitiesComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Item")
	class UInventoryItemData* ItemData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnUse();
};
