// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

USTRUCT(BlueprintType)
struct FInteractionPayload
{
	GENERATED_BODY()

	// reference al' attore
	UPROPERTY(BlueprintreadOnly)
	AActor* Interactor;

	// vettore che salva una posizione
	UPROPERTY(BlueprintreadOnly)
	FVector Location;
};
// delegato che non ci hanno ancora spiegato
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionHandler, FInteractionPayload, Payload);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERMOVEMENT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	// Called when the game starts

	// Stringa contenente il nome della interazione in corso
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Interaction")
	FString InteractionName;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame

	// parte del delegato
	UPROPERTY(BlueprintAssignable)
	FInteractionHandler OnInteract;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// funzione che viene chiamata quando si interagisce con un attore interagibile
	UFUNCTION(BlueprintCallable)
	virtual void Interact(FInteractionPayload Payload);

	// self explanatory
	UFUNCTION(BlueprintCallable)
	FString GetInteractionName() const;
	
};
