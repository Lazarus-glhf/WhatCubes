// Fill out your copyright notice in the description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Data/Enum/BlockType.h"
#include "Data/Enum/FaceDirection.h"
#include "Data/Structs/FMeshData.h"
#include "Chunk.generated.h"

UCLASS()
class WHATCUBES_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly)
	TArray<EBlockType> Blocks;

	/**
	 * @brief
	 * 一个 Block 里 8 个顶点的相对坐标
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> BlockVertices {
		FVector(100, 100, 100),
		FVector(100, 0, 100),
		FVector(100, 0, 0),
		FVector(100, 100, 0),
		FVector(0, 100, 100),
		FVector(0, 0, 100),
		FVector(0),
		FVector(0, 100, 0)
	};

	/**
	 * @brief
	 * 构成 Block 的 12 个三角形的顶点的索引
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> BlockTriangles {
		0, 1, 2, 3, // Front
		4, 0, 3, 7, // Right
		5, 4, 7, 6, // Back
		1, 5, 6, 2, // Left
		1, 0, 4, 5, // Top
		3, 2, 6, 7  // Down
	};

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> BlockUV {
		FVector2D(1, 0),
		FVector2D(0, 0),
		FVector2D(0, 1),
		FVector2D(1, 1)
	};
	
	UPROPERTY(BlueprintReadOnly)
	int RenderChunkSizeXY;

	UPROPERTY()
	TMap<int, FMeshData> MeshData;

	/**
	 * @brief 噪声指数，建议 0.01 ~ 0.00001
	 */
	UPROPERTY(BlueprintReadOnly)
	float Factor;

	/**
	 * @brief 根据 XYZ 计算出 在 Blocks 数组中的 index, Block 的 index 为 Z * ChunkSize ^ 2 + Y * ChunkSize + X		
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlockIndex(int X, int Y, int Z);

    /**
     * @brief 根据 Blocks 数组的 Index 值计算对应的 X 值
     * @param Index Blocks 数组的 Index 值
     * @return 对应的 X 值
     */
    UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlockXFromIndex(int Index);

    /**
     * @brief 根据 Blocks 数组的 Index 值计算对应的 Y 值
     * @param Index Blocks 数组的 Index 值
     * @return 对应的 Y 值
     */
    UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlockYFromIndex(int Index);

    /**
     * @brief 根据 Blocks 数组的 Index 值计算对应的 Z 值
     * @param Index Blocks 数组的 Index 值
     * @return 对应的 Z 值
     */
    UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlockZFromIndex(int Index);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetBlockMaterial(int BlockId);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void CreateBlocks(float InFactor);

	void GenerateMesh();

	/**
	 * @brief 将 Block 一个面的顶点索引和坐标加入 vertices 和 triangles
	 * @param Direction 需要渲染的是哪个面
	 * @param InPosition Block 的世界位置
	 */
	void CreateBlockFace(EFaceDirection Direction, const FVector& InPosition, const int BlockId = 0);

	/**
	 * @brief 计算传入面上各个顶点的世界坐标 
	 * @param Direction 传入的是哪个面 
	 * @param InPosition Block 的世界坐标
	 * @return 构成一个 Block 的所有顶点的世界坐标
	 */
	TArray<FVector> GetFaceVertices(EFaceDirection Direction, const FVector& InPosition);

	/**
	 * @brief 是否要生成面
	 */
	bool ShouldCreateFace(const FVector& InPosition);

	/**
	 * @brief 获得相邻坐标 
	 * @param Direction  
	 * @param InPosition 
	 * @return 
	 */
	FVector GetPositionInDirection(const EFaceDirection Direction, const FVector& InPosition);

};
