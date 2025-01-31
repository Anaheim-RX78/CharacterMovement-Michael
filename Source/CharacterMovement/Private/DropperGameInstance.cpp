// Fill out your copyright notice in the Description page of Project Settings.


#include "DropperGameInstance.h"

void UDropperGameInstance::OnLevelLoaded(FString LevelIdentifier)
{
	if (LevelIdentifier == CurrentLevelIdentifier)
	{
		//TODO: Reset Only some things
	}
	else
	{
		//TODO: Reset everything
	}
}
