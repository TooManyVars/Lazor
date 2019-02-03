// Fill out your copyright notice in the Description page of Project Settings.

#include "LazorSpawner.h"
#include "Classes/Components/BoxComponent.h"
#include "Engine.h"
#include "Lazor.h"


// Sets default values
ALazorSpawner::ALazorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setup spawn volume.
	spawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	spawnVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALazorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALazorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALazorSpawner::spawnLazor(FRotator rotation)
{
}

