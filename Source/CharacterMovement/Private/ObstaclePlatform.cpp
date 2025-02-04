// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePlatform.h"

#include "DropperGameInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstaclePlatform::AObstaclePlatform()
{
 
	PrimaryActorTick.bCanEverTick = true;

	// mesh come root componente e avilitato agli eventi di overlap
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstaclePlatform::OnOverlapBegin);
}


void AObstaclePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// evento di overlap 
void AObstaclePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Ostacolo Colpito");

	// controlla se l'attore sta overlappando il player
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// cast alla game instance
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());

		if (GameInstance) 
		{
			// setta il respawn del character prendendo dalla game instance l'ultimo checkpoint
			PlayerRespawnLocation = GameInstance->CheckpointLocation;
			PlayerCharacter->SetActorLocation(PlayerRespawnLocation);
			// richiama la funzione che si occupa di resettare lo score e le monete in caso di respawn
			GameInstance->DyingLol(10000);
		}
	}
}

// Called every frame
void AObstaclePlatform::Tick(float DeltaTime)
{
	// se deve muoversi qui cè il movimento sinuidale
	if (ShouldMove)
	{
		Super::Tick(DeltaTime);
		Time += DeltaTime*Speed;

		float t = FMath::Sin(Time)*0.5f + 0.5f;

		SetActorLocation(FMath::Lerp(InitialPosition, TargetPosition, t));
	}
}

