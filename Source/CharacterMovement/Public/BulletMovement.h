// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERMOVEMENT_API UBulletMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UPROPERTY(EditAnywhere)
	FVector Acceleration;

	UPROPERTY(EditAnywhere)
	FVector Gravity;

	UPROPERTY(EditAnywhere)
	float Drag;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(VisibleAnywhere)
	FVector Velocity;
	
	UBulletMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
