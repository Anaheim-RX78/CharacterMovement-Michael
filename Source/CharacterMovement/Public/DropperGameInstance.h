// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coin.h"
#include "Engine/GameInstance.h"
#include "DropperGameInstance.generated.h"

/**
 * Custom GameInstance for handling the scoring system.
 */
UCLASS()
class CHARACTERMOVEMENT_API UDropperGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Constructor
	UDropperGameInstance();

	// Total score across all levels
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int TotalScore;

	// Score for the current level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CurrentLevelScore;

	// Number of collected coins in the current level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CollectedCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	TArray<ACoin*> CoinArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int CoinsValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	FVector CheckpointLocation;

	// How fast the score decays per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float ScoreDecayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	bool ScoreFrozen=false;

	// Initializes the level score and resets collected coins
	UFUNCTION(BlueprintCallable, Category = "Score")
	void StartLevel(int InitialScore);

	// Decreases score over time
	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateScore(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Score")
	void DyingLol(int InitialScore);

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void ResetAllCoins();
	
	// Adds a coin to the collected count
	UFUNCTION(BlueprintCallable, Category = "Score")
	void CollectCoin();

	// Finalizes the level score and updates total score
	UFUNCTION(BlueprintCallable, Category = "Score")
	void FinishLevel();
};


