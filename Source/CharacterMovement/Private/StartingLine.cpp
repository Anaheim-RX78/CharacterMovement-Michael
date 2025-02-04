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

	// abilita la mesh a creare eventi overlap
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AStartingLine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AStartingLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// evento overlap
void AStartingLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// cast al character se è laltro membro d questo evento overlap
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		// cast alla game instance per richiamare start level
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

