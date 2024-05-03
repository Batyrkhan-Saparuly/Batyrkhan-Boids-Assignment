// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingAgent.h"

// Sets default values
AFlockingAgent::AFlockingAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockingAgent::BeginPlay()
{
	Super::BeginPlay();

	FlockingManager = Cast<AFlockingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AFlockingManager::StaticClass()));

	LocalFlockArea = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("Sphere"));

	if (LocalFlockArea) {
		LocalFlockArea->SetupAttachment(RootComponent);
		LocalFlockArea->RegisterComponent();
		LocalFlockArea->CreationMethod = EComponentCreationMethod::Instance;
		LocalFlockArea->SetSphereRadius(FlockingManager->GetLocalFlockRadius());
	}

	Velocity = GetActorForwardVector();
	Velocity = Velocity.GetSafeNormal();
	Velocity *= FMath::RandRange(FlockingManager->GetMinSpeed(), FlockingManager->GetMaxSpeed());

}

// Called every frame
void AFlockingAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Steer(DeltaTime);

	Cage();
}

void AFlockingAgent::Steer(float DeltaTime)
{
	FVector Acceleration = FVector::ZeroVector;

	TArray<AActor*> LocalFlock;
	LocalFlockArea->GetOverlappingActors(LocalFlock, AFlockingAgent::StaticClass());

	Acceleration += Separate(LocalFlock);
	Acceleration += Align(LocalFlock);
	Acceleration += Cohesion(LocalFlock);


	Velocity += Acceleration * DeltaTime;
	Velocity = Velocity.GetClampedToSize(FlockingManager->GetMinSpeed(), FlockingManager->GetMaxSpeed());
	SetActorLocation(GetActorLocation() + (Velocity * DeltaTime));
	SetActorRotation(Velocity.ToOrientationQuat());
}

void AFlockingAgent::Cage()
{
	FVector CurrentLocation = GetActorLocation();

	if (CurrentLocation.X < -1000) {
		CurrentLocation.X = 1000;
	}

	else if (CurrentLocation.X > 1000) {
		CurrentLocation.X = -1000;
	}

	if (CurrentLocation.Y < -1000) {
		CurrentLocation.Y = 1000;
	}

	else if (CurrentLocation.Y > 1000) {
		CurrentLocation.Y = -1000;
	}

	if (CurrentLocation.Z < -1000) {
		CurrentLocation.Z = 1000;
	}

	else if (CurrentLocation.Z > 1000) {
		CurrentLocation.Z = -1000;
	}

	SetActorLocation(CurrentLocation);
}

FVector AFlockingAgent::Separate(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;
	FVector SeparationDirection = FVector::ZeroVector;

	int FlockCount = 0;

	for (AActor* OtherAgent : LocalFlock) {
		if (OtherAgent != nullptr && OtherAgent != this) {

			float DistanceToOtherAgent = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

			if (DistanceToOtherAgent > FlockingManager->GetSeparationRadius()) {
				continue;
			}

			SeparationDirection = GetActorLocation() - OtherAgent->GetActorLocation();
			SeparationDirection = SeparationDirection.GetSafeNormal();
			Steering += SeparationDirection;

			FlockCount++;
		}

		if (FlockCount > 0) {
			Steering /= FlockCount;
			Steering = Steering.GetSafeNormal();
			Steering -= Velocity.GetSafeNormal();
			Steering *= FlockingManager->GetSeparationStrength();

			return Steering;
		}

	}

	return FVector();
}

FVector AFlockingAgent::Align(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;

	int FlockCount = 0;

	for (AActor* OtherAgent : LocalFlock) {
		if (OtherAgent != nullptr && OtherAgent != this) {

			AFlockingAgent* OtherBoid = Cast<AFlockingAgent>(OtherAgent);

			float DistanceToOtherAgent = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

			if (DistanceToOtherAgent > FlockingManager->GetAlignmentRadius()) {
				continue;
			}

			Steering += OtherBoid->Velocity.GetSafeNormal();
			Steering = Steering.GetSafeNormal();

			FlockCount++;
		}

		if (FlockCount > 0) {
			Steering /= FlockCount;
			Steering = Steering.GetSafeNormal();
			Steering -= Velocity.GetSafeNormal();
			Steering *= FlockingManager->GetAlignmentStrength();

			return Steering;
		}

	}

	return FVector();
}

FVector AFlockingAgent::Cohesion(TArray<AActor*> LocalFlock)
{
	FVector Steering = FVector::ZeroVector;
	FVector AvgPosition;

	int FlockCount = 0;

	for (AActor* OtherAgent : LocalFlock) {
		if (OtherAgent != nullptr && OtherAgent != this) {

			float DistanceToOtherAgent = FVector::Distance(GetActorLocation(), OtherAgent->GetActorLocation());

			if (DistanceToOtherAgent > FlockingManager->GetCohesionRadius()) {
				continue;
			}

			AvgPosition += OtherAgent->GetActorLocation();

			FlockCount++;
		}

		if (FlockCount > 0) {
			AvgPosition /= FlockCount;
			Steering = AvgPosition - GetActorLocation();
			Steering = Steering.GetSafeNormal();
			Steering -= Velocity.GetSafeNormal();
			Steering *= FlockingManager->GetCohesionStrength();

			return Steering;
		}

	}

	return FVector();
}

