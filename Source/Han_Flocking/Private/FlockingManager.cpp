// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"

// Sets default values
AFlockingManager::AFlockingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlockingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFlockingManager::GetMinSpeed()
{
	return MinSpeed;
}

float AFlockingManager::GetMaxSpeed()
{
	return MaxSpeed;
}

float AFlockingManager::GetLocalFlockRadius()
{
	return LocalFlockRadius;
}

float AFlockingManager::GetSeparationRadius()
{
	return SeparationRadius;
}

float AFlockingManager::GetSeparationStrength()
{
	return SeparationStrength;
}

float AFlockingManager::GetAlignmentRadius()
{
	return AlignmentRadius;
}

float AFlockingManager::GetAlignmentStrength()
{
	return AlignmentStrength;
}

float AFlockingManager::GetCohesionRadius()
{
	return CohesionRadius;
}

float AFlockingManager::GetCohesionStrength()
{
	return CohesionStrength;
}

