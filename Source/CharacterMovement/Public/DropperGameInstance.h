// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coin.h"
#include "Engine/GameInstance.h"
#include "DropperGameInstance.generated.h"

UCLASS()
class CHARACTERMOVEMENT_API UDropperGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UDropperGameInstance();

	// Variabile che contiene lo score finale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int TotalScore;

	// variabile che contiene lo score del livello attualmente giocato
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CurrentLevelScore;

	// numero di monete collezzionate dal player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CollectedCoins;

	// array che conserva tutte le monete in scena per poterle resettare
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	TArray<ACoin*> CoinArray;

	// implementazione non completa di un item che temporanemante aumenterebbe il valore delle monete collezionate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CoinsValue = 1;

	// FVector della posizione del checkpoint per resplawnare il player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	FVector CheckpointLocation;

	// tasso di ricaduta dello score dal valore inziale di 10000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float ScoreDecayRate;

	//impedisce allo score di scendere mentre si aspetta di superare la linea di partenza
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	bool ScoreFrozen=false;

	// si assicura che lo score e le monete raccolte abbiamo valore default
	UFUNCTION(BlueprintCallable, Category = "Score")
	void StartLevel(int InitialScore);

	// funzione chiamata in tick per far scendere lo score overtime
	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateScore(float DeltaTime);

	// funzione che gestisce lo reset alla morte di alcune variabili
	UFUNCTION(BlueprintCallable, Category = "Score")
	void DyingLol(int InitialScore);

	// funzione che cicla l'array di coins per resettarle
	UFUNCTION(BlueprintCallable, Category = "Coins")
	void ResetAllCoins();
	
	// update delle coin raccolte
	UFUNCTION(BlueprintCallable, Category = "Score")
	void CollectCoin();

	// finalizza lo score del livello appena giocato e lo aggiunge allo score finale
	UFUNCTION(BlueprintCallable, Category = "Score")
	void FinishLevel();
};


