// Fill out your copyright notice in the Description page of Project Settings.


#include "DropperGameInstance.h"

#include "Coin.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UDropperGameInstance::UDropperGameInstance()
{
	TotalScore = 0;
	CurrentLevelScore = 0;
	CollectedCoins = 0;
	ScoreDecayRate = 5.0f; // Lose 10 points per second
}

void UDropperGameInstance::StartLevel(int InitialScore)
{
	CurrentLevelScore = InitialScore;
	CollectedCoins = 0;
	ScoreFrozen=false;
}

void UDropperGameInstance::UpdateScore(float DeltaTime)
{
	if (CurrentLevelScore > 0 && !ScoreFrozen)
	{
		CurrentLevelScore -= ScoreDecayRate * DeltaTime;
		CurrentLevelScore = FMath::Max(0, CurrentLevelScore); // Prevent negative score
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Yellow, FString::Printf(TEXT("Current Score: %d"), CurrentLevelScore));
	}
}

void UDropperGameInstance::DyingLol(int InitialScore)
{
	CurrentLevelScore = InitialScore;
	CollectedCoins = 0;
	ScoreFrozen=false;
	ResetAllCoins();
}

void UDropperGameInstance::ResetAllCoins()
{
	for (ACoin* Coin : CoinArray)
	{
		if (Coin)
		{
			Coin->ResetCoins();
		}
	}
}

void UDropperGameInstance::CollectCoin()
{
	CollectedCoins+=CoinsValue;
}

void UDropperGameInstance::FinishLevel()
{
	int LevelFinalScore = CurrentLevelScore * CollectedCoins;
	TotalScore += LevelFinalScore;
	ScoreFrozen=true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Score Livello: %d, Score Totale: %d"), LevelFinalScore, TotalScore));
}
