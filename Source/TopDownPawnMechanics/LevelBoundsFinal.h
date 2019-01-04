// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelBoundsFinal.generated.h"

UCLASS()
class TOPDOWNPAWNMECHANICS_API ALevelBoundsFinal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelBoundsFinal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent * boxCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overlap event destroys lazors when they leave the bounds of the level and are out of sight.
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
