// Fill out your copyright notice in the Description page of Project Settings.

#include "IDamageableInterface.h"
#include "FloatingPawn.h"
#include "Engine.h"


// Add default functionality here for any IIDamageableInterface functions that are not pure virtual.

void IIDamageableInterface::takeDamage_Implementation(AFloatingPawn * player, float amount)
{
	//Log that the player has been damaged.
	UE_LOG(LogTemp, Warning, TEXT("%s has taken damage due to lazor collision remaining health: %d/%d(%d)"), *player->GetName(), player->health, player->InitialHealth, (player->health/player->InitialHealth)*100);
	//Deduct health from the player.
	player->deductHealth(amount);
}
