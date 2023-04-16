// Fill out your copyright notice in the Description page of Project Settings.


#include "MCGameMode.h"

#include "Kismet/GameplayStatics.h"

AMCGameMode::AMCGameMode()
	: RenderingRange(4800), ChunkSize(1600)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMCGameMode::BeginPlay()
{
	Super::BeginPlay();

	UpdateLocation();

	AddChunk();
}

void AMCGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (UpdateLocation())
	{
		AddChunk();

		RemoveChunk();
	}
}

bool AMCGameMode::UpdateLocation()
{
	if (const UWorld* World = GetWorld(); World)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
		const FVector2D Location = FVector2D(PlayerPawn->GetActorLocation());
		if (!(ChunkLocation * ChunkSize).Equals(Location, 100))
		{
			ChunkLocation = Location / ChunkSize;
			return true;
		}
	}
	return false;
}

void AMCGameMode::AddChunk()
{
	const float ChunkNum = RenderingRange / ChunkSize; 
	for (int X = ChunkNum - ChunkLocation.X; X != (int)(ChunkNum + ChunkLocation.X); )
	{
		for (int Y = ChunkNum - ChunkLocation.Y;  Y != (int)(ChunkNum + ChunkLocation.Y); )
		{
			FVector2D ActualLoc = FVector2D(X * ChunkSize, Y * ChunkSize);
			if (FVector2D::Distance(ActualLoc, ChunkLocation * ChunkSize) <= RenderingRange)
			{
				FVector SpawnLoc = FVector(ActualLoc, 0);
				if (!AllChunks.Contains(ActualLoc))
				{
					AChunk* Ref = (AChunk*)(GetWorld()->SpawnActor(ActorToSpawn, &SpawnLoc));
					if (Ref)
					{
						GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Yellow, TEXT("Success on spawning"));
					}
					AllChunks.Add(ActualLoc, Ref);
				}
			}
			if (Y < ChunkNum + ChunkLocation.Y)
			{
				Y++;
			}
			else
			{
				Y--;
			}
		}
		if (X < ChunkNum + ChunkLocation.X)
		{
			X++;
		}
		else
		{
			X--;
		}
	}
}

void AMCGameMode::RemoveChunk()
{
	for (auto key : AllChunks)
	{
		if (FVector2D::Distance(ChunkLocation * ChunkSize, key.Key) > RenderingRange)
		{
			AChunk* DelChunk = *AllChunks.Find(key.Key);
			DelChunk->Destroy();
			AllChunks.Remove(key.Key);
		}
	}
}
