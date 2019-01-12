// Fill out your copyright notice in the Description page of Project Settings.

#include "Lazor.h"
#include "Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine.h"
#include "FloatingPawn.h"
#include "IDamageableInterface.h"


// Sets default values
ALazor::ALazor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup the static mesh.
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//Attach it to the root component.
	RootComponent = staticMesh;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->SetupAttachment(RootComponent);
	//Bind OnOverlap Event to the lazor's box collision componenent;
	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALazor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALazor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(lazorMovementHandle, this, &ALazor::moveLazor, lazorSpeed, true);
}

// Called every frame
void ALazor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALazor::moveLazor()
{
	//Get the forward vector so that you can move the lazor in whichever way is forward.
	//What we will add to the actor's current location to calculate a new location.
	FVector actorOffset = GetActorForwardVector() * 5;

	//The new location for the actor to teleport to.
	FVector newActorLocation = actorOffset + GetActorLocation();

	//Now, all we need to do is set teleport the actor to this new location.
	SetActorLocation(newActorLocation);
	//After this point, we need to set a timer so that this is done n number of times when beginplay starts.
}

void ALazor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Check whether what collided with the lazor was a player
	//AFloatingPawn * player = Cast<AFloatingPawn>(OtherActor);
	//if (player)
	//{
	//	//I HAVENT CHECKED IF (60-67 works yet) -  BE WEARY.//
	//	IIDamageableInterface * implementationCheck = Cast<IIDamageableInterface>(player);

	//	if (implementationCheck)
	//	{
	//		//make the player take damage(don't call the function directly, use the Execute_function() call.
	//		implementationCheck->Execute_takeDamage(player, player, Damage);
	//	}

		//If the lazor collided with the player check if it implements the IDamageble interface(it will, but this is good practice)
		//UKismetSystemLibrary::DoesImplementInterface(player, IIDamageableInterface::takeDamage());
		//Make the player take damage using the takeDamage function.
	//}
}
