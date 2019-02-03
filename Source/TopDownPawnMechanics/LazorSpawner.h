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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Lazor spawner")
	void spawnLazor(FRotator rotation);

	
	
};
