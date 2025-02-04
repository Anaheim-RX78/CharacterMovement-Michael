// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API AFinishLine : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishLine();

	// creazione di una mesh per eventi voerlap
	UPROPERTY(EditAnywhere, Category = "components")
	UStaticMeshComponent* MeshComponent;

	// variabile che contiene la destinazione del teletrasporto a fine livello per passare al prossimo
	UPROPERTY(EditAnywhere)
	FVector NextCheckpoint;
protected:
	virtual void BeginPlay() override;

	// evento overlap
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	virtual void Tick(float DeltaTime) override;

};
