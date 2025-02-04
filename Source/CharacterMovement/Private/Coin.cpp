// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "DropperGameInstance.h"
#include "Pinko.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->SetVisibility(true);
	if (UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance()))
	{
		GameInstance->CoinArray.Add(this);
	}
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APinko* PlayerCharacter = Cast<APinko>(OtherActor);
	if (PlayerCharacter)
	{
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->CollectedCoins+=1;
			UE_LOG(LogTemp, Warning, TEXT("Score: %d"), GameInstance->CollectedCoins);
			MeshComponent->SetVisibility(false);
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SetActorEnableCollision(false);
		}
	}
}

void ACoin::ResetCoins()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetVisibility(true);
}



