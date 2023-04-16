// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "SimplexNoise/Public/SimplexNoiseBPLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector ActorLocation = GetActorLocation();
	
	for (int X = 0; X < 16; X++)
	{
		for (int Y = 0; Y < 16; Y++)
		{
			const float XPos = X * 100 + floor(ActorLocation.X);
			const float YPos = Y * 100 + floor(ActorLocation.Y);
			const float ZPos = floor(USimplexNoiseBPLibrary::SimplexNoiseInRange2D(XPos, YPos, 0, 32, 0.0001)) * 100;
			
			Mesh->AddInstance(FTransform(FVector(X * 100, Y * 100, ZPos)));
		}
	}
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
