// Fill out your copyright notice in the Description page of Project Settings.

#include "IDamageableInterface.h"
#include "FloatingPawn.h"
#include "Engine.h"


// Add default functionality here for any IIDamageableInterface functions that are not pure virtual.

void IIDamageableInterface::damagePlayer_Implementation(AFloatingPawn * player, float amount)
{
	//Deduct health from the player.
	player->deductHealth(amount);
	//Log that the player has taken damage, and what their remaining health is.
	UE_LOG(LogTemp, Warning, TEXT("%s's health is now %f."), *player->GetName(), player->health);
}
