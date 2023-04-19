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

	/** 设定区块由多少个 Block 组成，每个 Block 都被包含在 Blocks 数组中，并记录了其种类 */
	Blocks.SetNum(RenderChunkSizeXY * RenderChunkSizeXY * RenderChunkSizeXY);

	CreateBlocks(Factor);

	GenerateMesh();

	Mesh->CreateMeshSection(0, Vertices, Triangles, TArray({FVector()}), UV0, BlockVertexColors, TArray({FProcMeshTangent()}), false);
	SetBlockMaterial();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChunk::CreateBlocks(float InFactor)
{
	/** 获取 Chunk 坐标 */
	const FVector ActorLocation = GetActorLocation();

	for (int X = 0; X < RenderChunkSizeXY; X++)
	{
		for (int Y = 0; Y < RenderChunkSizeXY; Y++)
		{
			/** 生成 Block 的实际坐标 */ 
			const float XPos = X * 100 + floor(ActorLocation.X);
			const float YPos = Y * 100 + floor(ActorLocation.Y);
			/** 噪声 */
			const float ZPos = floor(USimplexNoiseBPLibrary::SimplexNoiseInRange2D(XPos, YPos, 0, RenderChunkSizeXY, InFactor));

			/** 将 Chunk 内 ZPos 及以下的方块标记为 Stone 需要渲染，否则标记为 Air 无需渲染 */
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
	const int IndexBound = GetBlockIndex(RenderChunkSizeXY - 1, RenderChunkSizeXY - 1, RenderChunkSizeXY - 1) + 1;
	for (int Index = 0; Index != IndexBound; ++Index)
	{
		const int X = GetBlockXFromIndex(Index);
		const int Y = GetBlockYFromIndex(Index);
		const int Z = GetBlockZFromIndex(Index);

		/** 若为实体方块 */
		if (Blocks[Index] > EBlockType::Air)
		{
			/** 遍历六个面 */
			for (int i = 0; i < 6; ++i)
			{
				const EFaceDirection Direction = static_cast<EFaceDirection>(i);
				FVector BlockPos = FVector(X, Y, Z);
				if (ShouldCreateFace(GetPositionInDirection(Direction, BlockPos)))
				{
					CreateBlockFace(Direction, BlockPos * 100);
				}
		    }
		}
	}
}

void AChunk::CreateBlockFace(EFaceDirection Direction, const FVector& InPosition)
{
	/** 添加顶点坐标 */
	Vertices.Append(GetFaceVertices(Direction, InPosition));

	/** 添加顶点索引 */
	const int VerticesNum = Vertices.Num();
	Triangles.Append({ VerticesNum + 0, VerticesNum + 3, VerticesNum + 1, VerticesNum + 1, VerticesNum + 3, VerticesNum + 2 });

	/** 添加顶点颜色 */
	const int alpha = static_cast<int>(Direction) * 255 / 6;	// RGBA 0 ~ 255
	FColor Color = FColor(alpha, alpha, alpha, alpha);
	BlockVertexColors.Append({Color, Color, Color, Color});

	/** 添加 UV */
	UV0.Append(BlockUV);
}

 TArray<FVector> AChunk::GetFaceVertices(EFaceDirection Direction, const FVector& InPosition)
{
	TArray<FVector> FaceVertices;

	/** 每个面需要 4 个索引构成 2 个三角形，所以需要 * 4，即步长为 4 */
	const int StartIndex = static_cast<int>(Direction) * 4;

	for (int i = StartIndex; i < StartIndex + 4; ++i)
	{
		/** 将此顶点的世界坐标加入到数组中 */
		FaceVertices.Add(BlockVertices[BlockTriangles[i]] + InPosition);
	}

	return FaceVertices;
}

int AChunk::GetBlockIndex(int X, int Y, int Z)
{
	return X + RenderChunkSizeXY * (Y + RenderChunkSizeXY * Z);
	// return X + Y * RenderChunkSizeXY + Z * RenderChunkSizeXY * RenderChunkSizeXY;
}

int AChunk::GetBlockXFromIndex(int Index)
{
	return Index % RenderChunkSizeXY;
}

int AChunk::GetBlockYFromIndex(int Index)
{
	return Index / RenderChunkSizeXY % RenderChunkSizeXY;
}

int AChunk::GetBlockZFromIndex(int Index)
{
	return Index / (RenderChunkSizeXY * RenderChunkSizeXY) % RenderChunkSizeXY;
}

bool AChunk::ShouldCreateFace(const FVector& InPosition)
{
	// 判断输入索引是否为边界值，避免越界
	if (InPosition.X < 0 || InPosition.Y < 0 || InPosition.Z <0 || InPosition.Z >= RenderChunkSizeXY || InPosition.X >= RenderChunkSizeXY || InPosition.Y >= RenderChunkSizeXY)
	{
		return true;	
	}

	// 若相邻方块不为实体
	if (Blocks[GetBlockIndex(InPosition.X, InPosition.Y, InPosition.Z)] <= EBlockType::Air)
	{
		return true;
	}
	return false;
}

FVector AChunk::GetPositionInDirection(const EFaceDirection Direction, const FVector& InPosition)
{
	FVector OutPos;
	
	switch (Direction)
	{
	case EFaceDirection::Forward :
		OutPos = FVector(1, 0, 0);
		break;
	case EFaceDirection::Right :
		OutPos = FVector(0, 1, 0);
		break;
	case EFaceDirection::Back :
		OutPos = FVector(-1, 0, 0);
		break;
	case EFaceDirection::Left :
		OutPos = FVector(0, -1, 0);
		break;
	case EFaceDirection::Up :
		OutPos = FVector(0, 0, 1);
		break;
	case EFaceDirection::Down :
		OutPos = FVector(0, 0, -1);
		break;
	default:
		break;
	}

	return InPosition + OutPos;
}
