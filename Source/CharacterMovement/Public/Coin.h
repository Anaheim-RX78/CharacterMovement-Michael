// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	

	ACoin();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent; //mesh di default per tutte le monete

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()

	//funzione che controlla se l'attore è in overlap con un altro attore.
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//funzione per respawnare le con in scena dopo che si muore
	void ResetCoins();
};
