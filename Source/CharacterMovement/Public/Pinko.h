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

	// bool che serve al toggle per transitare dal glidare alla caduta libera
	UPROPERTY(EditAnywhere,category = Movement)
	bool IsSlowFalling = false;

	// mesh del glider dal plugin skydiver
	UPROPERTY(VisibleAnywhere, Category = "Glider")
	UStaticMeshComponent* GliderMesh;

protected:
	// Called when the game starts or when spawned

	// non implementata nella verisone corrente
	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed = 100.0f;

	// gravity scale in caduta libera
	UPROPERTY(EditAnywhere,category = Movement)
	float FallingSpeedGravity = 1.5f;

	// gravity scale quando si apre il glider
	UPROPERTY(EditAnywhere,category = Movement)
	float FallingSpeedReducedGravity = 0.05f;

	// air control con il glider aperto
	UPROPERTY(EditAnywhere,category = Movement)
	float AirControl = 1.0f;

	// air control in caduta libera e quella di default a terra
	UPROPERTY(EditAnywhere,category = Movement)
	float ReducedAirControl = 0.1f;

	// forza salto, incrementata per contrastare la gravity scale superiore al normale
	UPROPERTY(EditAnywhere, Category = Movement)
	float JumpForce = 300.0f;

	// forza verticale per decelerare la caduta quando apri il glider
	UPROPERTY(EditAnywhere, Category = Movement)
	float UpdraftForce = 1.0f;

	// player camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	// apring arm al quale mettiamo il componente del interact
	UPROPERTY(editAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	// il component interact in questione
	UPROPERTY(EditAnywhere, Category = Interaction)
	UPlayerInteractionComponent* InteractionComponent;

	
	
	virtual void BeginPlay() override;

public:

	// componente inventario
	UPROPERTY(EditAnywhere, Category = Inventory)
	UInventory* Inventory;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// movimento del character 
	void SetMovementInput(const FVector2D& MovementInput);

	// rotazione telecamera con il mouse
	void SetLookInput(const FVector2D& LookInput);

	// la funzione che cambia le proprietà della gravita e air control e il glider
	void ToggleSlowFall();

	// evento on landed che rimuove il glider e resetta la gravità a quella non ridotta
	virtual void Landed(const FHitResult& Hit) override;

	// non implemenatto
	void ForwardBoost();

	UPlayerInteractionComponent* GetInteracionComponent();
};

