// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Engine.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialise the static mesh.
	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	//attach mesh to rootcomponent.
	RootComponent = collisionMesh;

	//initialise the projectile movement componenet.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	
	//set the component that the movement component will influence.
	ProjectileMovementComponent->SetUpdatedComponent(collisionMesh);

	//set properties for the projectile movement component.
	ProjectileMovementComponent->InitialSpeed = 10.0f;
	ProjectileMovementComponent->MaxSpeed = 10.0f;
	
	//This projectile will constantly have it's rotation updated to match the direction of the velocity.
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	//set the gravity for the bullet(in our game it should be 0).
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// Die after 3 seconds.
	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Decide the direction in which to send the bullet when it is fired.
void ABullet::shootInDirection(const FVector& shotDirection)
{
	/**
		How the math for calculating the direction to shoot works:
		- shotDirection is initally a unit vector(vector with magnitude 1, used to keep track of only a direction) until it is multiplied by the initial speed of the movement component, seeding the velocity magnitude.
		- Direction is determined by doing  origin(magnitude) - targetLocation(magnitude)
	**/

	ProjectileMovementComponent->Velocity = shotDirection * ProjectileMovementComponent->InitialSpeed;
}

