// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstaclePlatform.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API AObstaclePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstaclePlatform();
	// mesh di default
	UPROPERTY(EditAnywhere, Category = "components")
	UStaticMeshComponent* MeshComponent;

	// FVector per la posizione di respawn quando il character collide con questo attore e "muore"
	UPROPERTY(EditAnywhere)
	FVector PlayerRespawnLocation;

	UPROPERTY(VisibleAnywhere)
	float Time = 0; // codice reciclato dal progetto ostacoli

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false; // implementazione pigra del codice riciclato per non impostare la initial position
	
	UPROPERTY(EditAnywhere)
	FVector InitialPosition; // punto A del movimento dell attore

	UPROPERTY(EditAnywhere)
	FVector TargetPosition; // punto B

	UPROPERTY(EditAnywhere)
	FVector TotalMovement; // puoi specificare la distanza unità senza avere un punto B (viene calcolato usando questa variabile)

	UPROPERTY(EditAnywhere)
	float Speed = 1; // velocità del movimento sinuidale
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// standard implementazione di overlap con la mesh
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
