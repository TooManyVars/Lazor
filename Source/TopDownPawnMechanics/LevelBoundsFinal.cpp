// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBoundsFinal.h"
#include "Engine.h"
#include "Classes/Components/BoxComponent.h"
#include "Lazor.h"

// Sets default values
ALevelBoundsFinal::ALevelBoundsFinal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setup box collision
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->SetupAttachment(RootComponent);

	//Add nessecary end overlap event
	boxCollision->OnComponentEndOverlap.AddDynamic(this, &ALevelBoundsFinal::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ALevelBoundsFinal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelBoundsFinal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelBoundsFinal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Cast the actor to our lazor.
	ALazor * lazor = Cast<ALazor>(OtherActor);
	//If the cast is valid
	if (lazor)
	{
		//Log the collision
		UE_LOG(LogTemp, Warning, TEXT("%s has left the bounds of the level and been destroyed."), *lazor->GetName());

		//Destroy the actor.
		lazor->Destroy();
	}
}

