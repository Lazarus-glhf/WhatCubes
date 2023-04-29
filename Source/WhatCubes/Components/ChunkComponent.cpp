// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkComponent.h"

#include "SimplexNoiseBPLibrary.h"
#include "WhatCubes/Actors/WorldManager.h"


// Sets default values for this component's properties
UChunkComponent::UChunkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void UChunkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UChunkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UChunkComponent::GenerateTerrain() const
{
	UGlobalInfo* GlobalInfo = WorldManager->GlobalInfo;
	const int ChunkWidth = WorldManager->ChunkWidth;
	
	for (int X = 0; X < ChunkWidth; X++)
	{
		for (int Y = 0; Y <ChunkWidth; Y++)
		{
			// 生成 Block 的实际坐标
			const int XPos = (X + ChunkPosition.X * 16) * 100;
			const int YPos = (Y + ChunkPosition.Y* 16) * 100;
			// 噪声
			const int ZPeak = USimplexNoiseBPLibrary::SimplexNoiseInRange2D(XPos, YPos, 0, 16, 0.0001);
			
			// 根据 Z 生成不同的方块
			
			UE_LOG(LogTemp, Warning, TEXT("Generate Block at %d, %d, %d"),XPos, YPos, ZPeak);
			// EBlockType* Block = GlobalInfo->GlobalBlocksID.Find(BlockPos);
			EBlockType Block;
			GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, 0), EBlockType::BedRock);
			GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, ZPeak * 100), EBlockType::Grass);
			for (int Z = ZPeak - 1, layer = 0; Z > 0; Z--, layer++)
			{
				if (layer < 2)
				{
					Block = EBlockType::Dirt;
				}
				else
				{
					Block = EBlockType::Stone;
				}
				FVector BlockPos(XPos, YPos, Z * 100);
				GlobalInfo->BlocksNeedToCreate.Add(BlockPos, Block);
			}
		}
	}
}


