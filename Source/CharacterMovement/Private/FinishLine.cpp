// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "GameFramework/Character.h"
#include "DropperGameInstance.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFinishLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Ostacolo Colpito");
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// Get Game Instance and cast it
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());

		if (GameInstance) 
		{
			GameInstance->FinishLevel();
			// Get the stored respawn location
			GameInstance->CheckpointLocation = NextCheckpoint;
			PlayerCharacter->SetActorLocation(NextCheckpoint);
		}
	}
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

