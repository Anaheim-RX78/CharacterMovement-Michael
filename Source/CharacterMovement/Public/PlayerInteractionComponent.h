// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractableComponent.h"
#include "PlayerInteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERMOVEMENT_API UPlayerInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPlayerInteractionComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance = 1000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	//FName InteractionProfile = "Interaction";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> InteractionChannel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractableComponent* CurrentInteractable = nullptr;
	
	virtual void BeginPlay() override;

	void CheckInteractionRange();
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Interact();
};
