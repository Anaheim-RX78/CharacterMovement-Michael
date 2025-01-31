// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInteractionComponent::CheckInteractionRange()
{
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, GetComponentLocation(), GetComponentLocation() + (GetForwardVector() * InteractionDistance), InteractionChannel);
	
	//GetWorld()->LineTraceSingleByProfile(HitResult, GetComponentLocation(), GetForwardVector() * InteractionDistance, InteractionProfile);

	AActor* HitActor = HitResult.GetActor();

	if (HitActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Emerald, TEXT(" No Interactable Found"));
		CurrentInteractable = nullptr;
		return;
	}
	
	UInteractableComponent* Component = HitResult.GetActor()->GetComponentByClass<UInteractableComponent>();

	if (CurrentInteractable == nullptr && Component)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Interactable Found"));
		CurrentInteractable = Component;
	}
	else if (CurrentInteractable && Component && Component != CurrentInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Interactable Replaced"));
		CurrentInteractable = Component;
	}
}

void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckInteractionRange();
}

void UPlayerInteractionComponent::Interact()
{
	if (CurrentInteractable == nullptr) return;

	CurrentInteractable->Interact(FInteractionPayload{GetOwner()});
}
