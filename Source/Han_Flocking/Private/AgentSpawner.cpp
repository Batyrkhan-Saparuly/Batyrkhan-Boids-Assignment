// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentSpawner.h"

// Sets default values
AAgentSpawner::AAgentSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < SpawnCount; i++) {

		FVector SpawnPosition;

		if (SpawnInCenter) {
			SpawnPosition = FVector(0, 0, 0);
		}

		else {
			SpawnPosition = GetRandomVector(-SpawnArea, SpawnArea);
		}

		FRotator SpawnRotation(0, FMath::RandRange(-180, 180), 0);

		AFlockingAgent* FlockingAgent = GetWorld()->SpawnActor<AFlockingAgent>(ActorToSpawn, SpawnPosition, SpawnRotation);
	}
}

// Called every frame
void AAgentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AAgentSpawner::GetRandomVector(double Min, double Max)
{
	FVector RandomVector(FMath::RandRange(Min, Max), FMath::RandRange(Min, Max), 0);

	return RandomVector;
}
