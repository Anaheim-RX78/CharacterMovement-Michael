// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePlatform.h"

#include "DropperGameInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstaclePlatform::AObstaclePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstaclePlatform::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AObstaclePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstaclePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Ostacolo Colpito");
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// Get Game Instance and cast it
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());

		if (GameInstance) 
		{
			// Get the stored respawn location
			PlayerRespawnLocation = GameInstance->CheckpointLocation;
			PlayerCharacter->SetActorLocation(PlayerRespawnLocation);
			GameInstance->DyingLol(10000);
		}
	}
}

// Called every frame
void AObstaclePlatform::Tick(float DeltaTime)
{
	if (ShouldMove)
	{
		Super::Tick(DeltaTime);
		Time += DeltaTime*Speed;

		float t = FMath::Sin(Time)*0.5f + 0.5f;

		SetActorLocation(FMath::Lerp(InitialPosition, TargetPosition, t));
	}
}

