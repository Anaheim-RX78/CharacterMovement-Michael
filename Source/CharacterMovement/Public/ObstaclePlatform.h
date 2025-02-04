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
	UPROPERTY(EditAnywhere, Category = "components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	FVector PlayerRespawnLocation;

	UPROPERTY(VisibleAnywhere)
	float Time = 0;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;
	
	UPROPERTY(EditAnywhere)
	FVector InitialPosition;

	UPROPERTY(EditAnywhere)
	FVector TargetPosition;

	UPROPERTY(EditAnywhere)
	FVector TotalMovement;

	UPROPERTY(EditAnywhere)
	float Speed = 1;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
