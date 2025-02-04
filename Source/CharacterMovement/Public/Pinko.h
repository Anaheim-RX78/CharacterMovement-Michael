// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Inventory.h"
#include "PlayerInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pinko.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API APinko : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APinko();
	
	UPROPERTY(EditAnywhere,category = Movement)
	bool IsSlowFalling = false;

	UPROPERTY(VisibleAnywhere, Category = "Glider")
	UStaticMeshComponent* GliderMesh;

protected:
	// Called when the game starts or when spawned

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed = 100.0f;
	
	UPROPERTY(EditAnywhere,category = Movement)
	float FallingSpeedGravity = 1.5f;

	UPROPERTY(EditAnywhere,category = Movement)
	float FallingSpeedReducedGravity = 0.05f;

	UPROPERTY(EditAnywhere,category = Movement)
	float AirControl = 1.0f;

	UPROPERTY(EditAnywhere,category = Movement)
	float ReducedAirControl = 0.1f;
	
	UPROPERTY(EditAnywhere, Category = Movement)
	float JumpForce = 300.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float UpdraftForce = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(editAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Interaction)
	UPlayerInteractionComponent* InteractionComponent;

	
	
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = Inventory)
	UInventory* Inventory;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMovementInput(const FVector2D& MovementInput);

	void SetLookInput(const FVector2D& LookInput);

	void ToggleSlowFall();

	virtual void Landed(const FHitResult& Hit) override;

	void ForwardBoost();

	UPlayerInteractionComponent* GetInteracionComponent();
};

