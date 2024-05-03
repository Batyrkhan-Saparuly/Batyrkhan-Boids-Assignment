// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "FlockingManager.h"
#include "FlockingAgent.generated.h"

UCLASS()
class HAN_FLOCKING_API AFlockingAgent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlockingAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	FVector Velocity;

protected:

	void Steer(float DeltaTime);
	void Cage();
	AFlockingManager* FlockingManager;
	USphereComponent* LocalFlockArea;

	//Separation
	FVector Separate(TArray<AActor*> LocalFlock);

	//Alignment
	FVector Align(TArray<AActor*> LocalFlock);

	//Cohesion
	FVector Cohesion(TArray<AActor*> LocalFlock);
};
