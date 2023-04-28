// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "Kismet/GameplayStatics.h"
#include "SimplexNoise/Public/SimplexNoiseBPLibrary.h"
#include "WhatCubes/Chunk.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	
	Seed = 123;
	USimplexNoiseBPLibrary::setNoiseSeed(Seed);

	ChunkNum = RenderingRange / ChunkSize;

	ShouldUpdatePlayerCoordinate();

	AddChunk();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldUpdatePlayerCoordinate())
	{
		AddChunk();
		RemoveChunk();
	}
}

bool AWorldManager::ShouldUpdatePlayerCoordinate()
{
	if (const UWorld* World = GetWorld(); World)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
		const FVector2D Location = FVector2D(PlayerPawn->GetActorLocation());
		if (!(LastPlayerChunkCoordinate * ChunkSize).Equals(Location, 100))
		{
			LastPlayerChunkCoordinate = Location / ChunkSize;
			return true;
		}
	}
	return false;
}

void AWorldManager::AddChunk()
{
	for (int X = LastPlayerChunkCoordinate.X - ChunkNum; X != static_cast<int>(LastPlayerChunkCoordinate.X + ChunkNum); )
	{
		for (int Y =  LastPlayerChunkCoordinate.Y - ChunkNum;  Y != static_cast<int>(LastPlayerChunkCoordinate.Y + ChunkNum); )
		{
			FVector2D CurrentChunkLocation = FVector2D(X * ChunkSize, Y * ChunkSize);
			// if (FVector2D::Distance(ActualLoc, LastPlayerChunkCoordinate * ChunkSize) <= RenderingRange)
			// {
			if (!AllChunks.Contains(CurrentChunkLocation))
			{
				// Call in Blueprint
				AChunk* Ref = GenerateChunk(FVector(CurrentChunkLocation, 0));
				AllChunks.Add(CurrentChunkLocation, Ref);
			// }
			}
			if (Y < ChunkNum + LastPlayerChunkCoordinate.Y) { Y++; }
			else { Y--; }
		}
		if (X < ChunkNum + LastPlayerChunkCoordinate.X) { X++; }
		else { X--; }
	}
}

void AWorldManager::RemoveChunk()
{
	for (auto key : AllChunks)
	{
		if (FVector2D::Distance(LastPlayerChunkCoordinate * ChunkSize, key.Key) > RenderingRange)
		{
			AChunk* DelChunk = *AllChunks.Find(key.Key);
			DelChunk->Destroy();
			AllChunks.Remove(key.Key);
		}
	}
}

AChunk* AWorldManager::GenerateChunk_Implementation(const FVector& Location)
{
	return GetWorld()->SpawnActor<AChunk>(Location, FRotator());
}

