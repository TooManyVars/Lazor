// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LazorSpawner.generated.h"

UCLASS()
class TOPDOWNPAWNMECHANICS_API ALazorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALazorSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent * spawnVolume;

	//The type of Lazor that we want to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor * lazorType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function to spawn lazors.
	UFUNCTION(BlueprintCallable, Category = "Lazor spawner")
	void spawnLazor(FRotator rotation);

	//Custom 'GetAllActorsOfType' function, given an arbitrary class(defined using template classes)
	//The parameters are world and out, world being the world to search for the given actor, and out being the array to add the actor to.
	template<typename t>
	void getAllActorsOfClass(UWorld* World, TArray<t*>& Out)
	{
		//Iterate through all actors in the world and add them to our out array.
		for (TActorIterator<t> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	}

};
