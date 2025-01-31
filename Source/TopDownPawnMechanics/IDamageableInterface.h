// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNPAWNMECHANICS_API IIDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Damages the player. can be expanded upon in blueprint if nessecary.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, category = "IDamageableInterface")
	void takeDamage(float amount);
};
