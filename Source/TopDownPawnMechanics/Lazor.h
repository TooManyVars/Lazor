// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lazor.generated.h"

UCLASS()
class TOPDOWNPAWNMECHANICS_API ALazor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALazor();

	//setup components here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent * boxCollision;

	//Dictates the speed of the lazors, aka how often times the moveLazor method is called in seconds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lazor")
	float lazorSpeed = 0.0045f;

	//Timer handle for the movement of the lazor.
	FTimerHandle lazorMovementHandle;

	//FX to play(at the location of the bullet collision) when the lazor is destroyed.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, category = "Lazor")
	void playDeathFX(FVector bulletImpactPoint);

	//The amount of damage the lazor can do to the player.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Lazor")
	float Damage = 500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Move the lazor ever so slightly. doing this multiple times per second makes the lazor look like it's sliding across the screen.
	UFUNCTION()
	void moveLazor();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
