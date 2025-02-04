// Fill out your copyright notice in the Description page of Project Settings.


#include "DropperGameInstance.h"

#include "Coin.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UDropperGameInstance::UDropperGameInstance()
{
	// valori default
	TotalScore = 0;
	CurrentLevelScore = 0;
	CollectedCoins = 0;
	ScoreDecayRate = 5.0f; // tasso di degrado dello score in tick
}

void UDropperGameInstance::StartLevel(int InitialScore)
{
	// valori default a inizio livello
	CurrentLevelScore = InitialScore;
	CollectedCoins = 0;
	ScoreFrozen=false;
}

void UDropperGameInstance::UpdateScore(float DeltaTime)
{
	// funzione chiamata in tick nel player character per aggiornare lo score
	if (CurrentLevelScore > 0 && !ScoreFrozen)
	{
		CurrentLevelScore -= ScoreDecayRate * DeltaTime;
		CurrentLevelScore = FMath::Max(0, CurrentLevelScore); // rimuove lo score negativo
	}
	
	if (GEngine)
	{
		// print dello score
		GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Yellow, FString::Printf(TEXT("Current Score: %d"), CurrentLevelScore));
	}
}

void UDropperGameInstance::DyingLol(int InitialScore)
{
	// resets the score and coins when player respawns
	CurrentLevelScore = InitialScore;
	CollectedCoins = 0;
	ScoreFrozen=false;
	ResetAllCoins();
}

void UDropperGameInstance::ResetAllCoins()
{
	// cicla l'array di coin preso in play per resettare le coin raccolte quando si muore
	for (ACoin* Coin : CoinArray)
	{
		if (Coin)
		{
			// funzione di reset in ACOin
			Coin->ResetCoins();
		}
	}
}

void UDropperGameInstance::CollectCoin()
{
	// contatore coin
	CollectedCoins+=CoinsValue;
}

void UDropperGameInstance::FinishLevel()
{
	// finalizza lo score dle livello appena giocato e stampa il valore di score
	int LevelFinalScore = CurrentLevelScore * CollectedCoins;
	TotalScore += LevelFinalScore;
	ScoreFrozen=true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Score Livello: %d, Score Totale: %d"), LevelFinalScore, TotalScore));
}
