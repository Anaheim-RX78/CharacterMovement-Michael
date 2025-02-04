// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartingLine.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API AStartingLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartingLine();

	// mesh
	UPROPERTY(EditAnywhere, Category = "components")
	UStaticMeshComponent* MeshComponent;

protected:
	virtual void BeginPlay() override;
	// funzione di overlap
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	virtual void Tick(float DeltaTime) override;
	

};
