// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FloatingPawn.generated.h"

UCLASS()
class TOPDOWNPAWNMECHANICS_API AFloatingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFloatingPawn();

	//Setup components here.
	//Where the bullets will be spawned relative to the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent * bulletLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFloatingPawnMovement * pawnMovementComponent;

	//setup components here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent * camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent * cameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Player")
	float InitialHealth = 1000.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, category = "Player")
	float health;

	//Whether or not the player is dead.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
	bool isDead;

	//Whether the player can spawn lazors or not(used only in debug)
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Debug")
	bool bCanSpawnLazors;

	//Vector which determines where to spawn bullets in relation to the player pawn.
	//EditAnywhere means that you can edit variables like this both within the editor as a default value and within specific instances of the pawn in game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Gameplay")
	FVector muzzleOffset;

	//The type of bullet to spawn.
	//EditDefaults only means that this variable can only be edited within the BP as a default value.
	UPROPERTY(EditDefaultsOnly, category = "Projectile")
	TSubclassOf<class ABullet> bulletType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Gameplay")
	float roundsPerSecond = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Gameplay")
	float turnSensitivity = 1.5f;

	FTimerHandle rapidFireTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void moveForward(float value);
	void moveRight(float value);

	//Take health from the player based on a certain value.
	UFUNCTION(BlueprintCallable, Category = "Player")
	virtual void deductHealth(float delta);

	//Checks the player's health to see if they should be dead or not.
	virtual void checkDead();

	//Spawns or "fires" a bullet.
	UFUNCTION(BlueprintNativeEvent)
	void fire();
	void fire_Implementation();
	
	//These lookUp and lookRight functions don't actually have any function and simply act as an empty binding for the axis.
	void lookUp(float value);
	void lookRight(float value);

	//Sets a timer to fire a bullet every set period of time
	void pullTrigger();

	//Clears the timer which fires the bullet every set period of time.
	void releaseTrigger();
};
