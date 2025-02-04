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

	//Impostata la mesh come root component e abilitata a creari eventi di overlap
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
	//mesh visibili on play
	MeshComponent->SetVisibility(true);
	//aggiunge tutte le monete in scena ad un array di monete che servirà per resettarle in scena
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
	//controlla se il risultato di voerlap con other actor è il player character
	APinko* PlayerCharacter = Cast<APinko>(OtherActor);
	if (PlayerCharacter)
	{
		//cast alla game instance
		UDropperGameInstance* GameInstance = Cast<UDropperGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			//ogni volta che il player overlappa con una moneta aumenta il valore di collectedcoins in game instance
			GameInstance->CollectedCoins+=1;
			UE_LOG(LogTemp, Warning, TEXT("Score: %d"), GameInstance->CollectedCoins);
			//rimuove la moneta dalla scena senza distruggere l'attore
			MeshComponent->SetVisibility(false);
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SetActorEnableCollision(false);
		}
	}
}

void ACoin::ResetCoins()
{
	//resetta le monete per renderle di nuovo visibili e interagibili in scena
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetVisibility(true);
}



