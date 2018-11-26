// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingPawn.h"
#include "Components/InputComponent.h" 
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "TimerManager.h"
#include "Bullet.h"


// Sets default values
AFloatingPawn::AFloatingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement"); //setup movement component so the pawn can move.

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = staticMesh;

	//camera setup
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//attach the camera boom to the rootComponent, and then the camera to the cameraBoom.
	cameraBoom->SetupAttachment(RootComponent);
	camera->SetupAttachment(cameraBoom);

	bulletLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletLocation"));
	bulletLocation->SetupAttachment(RootComponent);
	
}
// Called when the game starts or when spawned
void AFloatingPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloatingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Code to update the player's rotation relative to the movement of the mouse.
	AController * playerController = GetController();

	//Get the vector for the intended rotation of the characte using the input axis values.
	FVector lookVector(GetInputAxisValue("LookRight"), GetInputAxisValue("LookUp"), 0.0f);

	//Get the length of the vector by doing the sqrt of x^2 + y^2
	float lookVectorLength = FMath::Sqrt((lookVector.X*lookVector.X) + (lookVector.Y*lookVector.Y));

	//If this length is above a certain amount, set the control rotation relative to the movement of the mouse along the x and y axis.
	if (lookVectorLength > turnSensitivity)
	{
		playerController->SetControlRotation(lookVector.Rotation());
	}
}

// Called to bind functionality to input
void AFloatingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//setup the pawn to take inputs for forward and backward/left and right movement.
	//note that the difference between axis and action movements is that only axis movements can be done to a cetain extent, such as a half pressed joystick.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFloatingPawn::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFloatingPawn::moveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AFloatingPawn::lookRight);
	PlayerInputComponent->BindAxis("LookRight", this, &AFloatingPawn::lookUp);

	//Input actions.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFloatingPawn::pullTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFloatingPawn::releaseTrigger);
}

void AFloatingPawn::moveForward(float value)
{
	//Enable input for movement down the x axis by a certain amount.
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
}

void AFloatingPawn::moveRight(float value)
{
	//Enable input for movement down the y axis by a certain amount.
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
}

void AFloatingPawn::fire_Implementation()
{
	if (bulletType) //If bulletType isn't null.
	{
		//Get the world
		UWorld * world = GetWorld();

		//Check that world isn't null(it shouldn't).
		if (world)
		{
			//figure out what half of this code even does.
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			FVector bulletSpawnLocation = bulletLocation->GetComponentTransform().GetLocation();
			FRotator bulletRotation = GetActorRotation(); //get the curent rotation of the player.

			//Currently, i can get projectiles to spawn, but i can't get the movement direction right.
			//spawn the bullet into the world, providing a location, rotation and spawn parameters.
			ABullet * bullet = world->SpawnActor<ABullet>(bulletType, bulletSpawnLocation, bulletRotation, spawnParams);

			if (bullet)
			{
				bullet->shootInDirection(AFloatingPawn::GetActorForwardVector());
			}
		}
	}
}

void AFloatingPawn::pullTrigger()
{
	//Fire an inital shot before moving into the rapid fire sequence.
	fire();

	//Every n number of seconds, call the fire function, Leading to the player firing n rounds per second.
	GetWorld()->GetTimerManager().SetTimer(rapidFireTimerHandle, this, &AFloatingPawn::fire, roundsPerSecond, true);
}

void AFloatingPawn::releaseTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(rapidFireTimerHandle);
}

void AFloatingPawn::lookUp(float value)
{

}

void AFloatingPawn::lookRight(float value)
{

}

