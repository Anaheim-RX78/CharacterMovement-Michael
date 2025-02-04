// Fill out your copyright notice in the Description page of Project Settings.
#include "TelecomandoBoost.h"

#include "ItemsAbilities.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UTelecomandoBoost::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "TELECOMANDO ATTIVATO");
	
}
