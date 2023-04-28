// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManager.generated.h"

UCLASS()
class WHATCUBES_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Seed;

	/**
	 * %member
	 * @brief 维护的 Chunk 数量，由 RenderingRange 决定
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ChunkNum;

	/**
	 * %member
	 * @brief Chunk Map
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FVector2D, AChunk*> AllChunks;

	/**
	 * %member
	 * @brief 渲染距离
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int RenderingRange = 4800;

	/**
	 * %method
	 * @brief 每 Tick 都会触发，根据 ActorLocation 更新 ChunkLocation
	 * @return 当 Player 移动一段距离后返回 true
	 */
	UFUNCTION()
	bool ShouldUpdatePlayerCoordinate();

	/**
	 * %method
	 * @brief 在 RenderingRange 内生成 Chunk
	 */
	UFUNCTION()
	void AddChunk();

	/**
	 * %method
	 * @brief 移除 RenderingRange 外的 Chunk  
	 */
	UFUNCTION()
	void RemoveChunk();

	UFUNCTION(BlueprintNativeEvent)
	AChunk* GenerateChunk(const FVector& Location);
	
private:
	/**
	 * %member
	 * @brief 上次更新时 Player 所在 Chunk 坐标
	 */
	FVector2D LastPlayerChunkCoordinate;

	/**
	 * %member
	 * @brief 区块宽度
	 */
	int ChunkSize = 1600;
};
