// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "GameFramework/Character.h"
#include "DropperGameInstance.h"


AFinishLine::AFinishLine()
{
	PrimaryActorTick.bCanEverTick = true;
// setup della mesh per ottenere eventi overlap
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
	// cast al player character se è l'attore che ha generato l'evento overlap
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Ostacolo Colpito");
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// cast alla game istance per recupera la funzione finish level
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());

		if (GameInstance) 
		{
			GameInstance->FinishLevel();
			// fornisce alla game instance il valore del vettore contenente il checkpoint del prossimo livello
			GameInstance->CheckpointLocation = NextCheckpoint;
			// teleport
			PlayerCharacter->SetActorLocation(NextCheckpoint);
		}
	}
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

