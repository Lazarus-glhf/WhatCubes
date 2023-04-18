// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

#include "SimplexNoise/Public/SimplexNoiseBPLibrary.h"

// Sets default values
AChunk::AChunk()
	: RenderChunkSizeXY(16), Factor(0.0001)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();

	/** Resize Blocks Length */
	Blocks.SetNum(RenderChunkSizeXY * RenderChunkSizeXY * RenderChunkSizeXY);

	CreateBlocks(Factor);

	GenerateMesh();

	Mesh->CreateMeshSection(0, Vertices, Triangles, TArray({FVector()}), BlockUV, TArray({FColor()}), TArray({FProcMeshTangent()}), false);
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChunk::CreateBlocks(float InFactor)
{
	const FVector ActorLocation = GetActorLocation();

	for (int X = 0; X < RenderChunkSizeXY; X++)
	{
		for (int Y = 0; Y < RenderChunkSizeXY; Y++)
		{
			const float XPos = X * 100 + floor(ActorLocation.X);
			const float YPos = Y * 100 + floor(ActorLocation.Y);
			const float ZPos = floor(USimplexNoiseBPLibrary::SimplexNoiseInRange2D(XPos, YPos, 0, RenderChunkSizeXY, InFactor));

			for (int Z = 0; Z < RenderChunkSizeXY; Z++)
			{
				if (Z <= ZPos) 
				{
					Blocks[GetBlockIndex(X, Y, Z)] = EBlockType::Stone;
				}
				else
				{
					Blocks[GetBlockIndex(X, Y, Z)] = EBlockType::Air;
				}
			}
		}
	}
}

void AChunk::GenerateMesh()
{
	for (int X = 0; X < RenderChunkSizeXY; ++X)
	{
		for (int Y = 0; Y < RenderChunkSizeXY; ++Y)
		{
			for (int Z = 0; Z < RenderChunkSizeXY; ++Z)
			{
				 if (Blocks[GetBlockIndex(X, Y, Z)] > EBlockType::Air )
				 {
					 for (int i = 0; i < 6; ++i)
					 {
						 CreateBlockFace(static_cast<EFaceDirection>(i), FVector(X, Y, Z) * 100);
					 }
				 }
			}
		}
	}
}

void AChunk::CreateBlockFace(EFaceDirection Direction, FVector InPosition)
{
	/** 创建顶点 */
	Vertices.Append(GetFaceVertices(Direction, InPosition));

	/** 创建三角形 */
	const int VerticesNum = Vertices.Num();
	Triangles.Append({ VerticesNum + 0, VerticesNum + 3, VerticesNum + 1, VerticesNum + 1, VerticesNum + 3, VerticesNum + 2 });
}

 TArray<FVector> AChunk::GetFaceVertices(EFaceDirection Direction, FVector InPosition)
{
	TArray<FVector> FaceVertices;
	
	const int StartIndex = static_cast<int>(Direction) * 4;

	for (int i = StartIndex; i < StartIndex + 4; ++i)
	{
		FaceVertices.Add(BlockVertices[BlockTriangles[i]] + InPosition);
	}

	return FaceVertices;
}

int AChunk::GetBlockIndex(int X, int Y, int Z)
{
	return  X + Y * RenderChunkSizeXY + Z * RenderChunkSizeXY * RenderChunkSizeXY;
}
