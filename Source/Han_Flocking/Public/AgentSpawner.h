// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlockingAgent.h"
#include "AgentSpawner.generated.h"

UCLASS()
class HAN_FLOCKING_API AAgentSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
	int SpawnCount = 35;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	int SpawnArea = 1800;

	UPROPERTY(EditAnywhere)
	bool SpawnInCenter = true;

protected:

	FVector GetRandomVector(double Min, double Max);
};
