// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkComponent.h"

#include "SimplexNoiseBPLibrary.h"
#include "Maths/MathUtils.h"
#include "WhatCubes/Actors/WorldManager.h"
#include "World/Biome/Biome.h"
#include "World/Biome/Biomes.h"


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
	const MathUtils::Coord ChunkPos {static_cast<CoordInt>(ChunkPosition.X), static_cast<CoordInt>(ChunkPosition.Y), 0};
	const Biome B = Biomes::GetInstance().GetBiome(WorldManager->Seed, ChunkPos);
	
	for (int X = 0; X < ChunkWidth; X++)
	{
		for (int Y = 0; Y < ChunkWidth; Y++)
		{
			// 生成 Block 的实际坐标
			const int XPos = (X + ChunkPosition.X * 16) * 100;
			const int YPos = (Y + ChunkPosition.Y * 16) * 100;
			// 噪声
			int ZPeak = USimplexNoiseBPLibrary::SimplexNoiseInRange2D(XPos, YPos, 0, 16, 0.0001);
			// TODO: 依旧多抬高一格，但是不太清楚需不需要再抬高。噪声函数之后会重写，这里肯定还会改的。其次是测试一下 Clamp 函数。
			ZPeak = MathUtils::Clamp(ZPeak + 1, 0, WorldManager->ChunkHeight);
			
			// 根据 Z 生成不同的方块
			
			// UE_LOG(LogTemp, Warning, TEXT("Generate Block at %d, %d, %d"),XPos, YPos, ZPeak);
			// EBlockType* Block = GlobalInfo->GlobalBlocksID.Find(BlockPos);
			EBlockType Block;
			switch (B.GetBiomeType())
			{
			case BiomeType::PLAIN:
				GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, ZPeak * 100), EBlockType::Grass);
				break;
			case BiomeType::DESERT:
				GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, ZPeak * 100), EBlockType::Dirt);
				break;
			case BiomeType::RIVER:
				GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, ZPeak * 100), EBlockType::BedRock);
				break;
			}
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

			// 确保 Bedrock 一定是垫底的
			GlobalInfo->BlocksNeedToCreate.Add(FVector(XPos, YPos, 0), EBlockType::BedRock);
		}
	}
}


