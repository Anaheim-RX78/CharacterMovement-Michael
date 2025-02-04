// Fill out your copyright notice in the Description page of Project Settings.


#include "StartingLine.h"
#include "GameFramework/Character.h"
#include "DropperGameInstance.h"

// Sets default values
AStartingLine::AStartingLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AStartingLine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AStartingLine::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStartingLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// Get Game Instance and cast it
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());

		if (GameInstance) 
		{
			GameInstance->StartLevel(10000);
		}
	}
}

// Called every frame
void AStartingLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

