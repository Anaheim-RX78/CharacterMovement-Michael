// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMovement.h"

// Sets default values for this component's properties
UBulletMovement::UBulletMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletMovement::BeginPlay()
{
	Super::BeginPlay();

	Velocity =Acceleration;
	
}


// Called every frame
void UBulletMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector WorldVelocity = GetOwner()->GetTransform().TransformVector(Velocity);
	
	FVector NextPosition = GetOwner()->GetActorLocation() + Velocity * DeltaTime * Drag;
	Velocity.Z -= Gravity.Z * DeltaTime;

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, GetOwner()->GetActorLocation(), NextPosition, CollisionChannel))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("The bullet has hit something"));
		GetOwner()->Destroy();
	}
	GetOwner()->SetActorLocation(NextPosition);
}

