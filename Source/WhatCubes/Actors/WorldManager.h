// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhatCubes/Components/ChunkComponent.h"
#include "WhatCubes/Components/GlobalInfo.h"
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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UGlobalInfo* GlobalInfo;
	
	/**
	 * @brief 世界生成种子
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Seed;

	/**
	 * @brief 区块更新差值
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float UpdateDistance = 500;

	/**
	 * @brief 维护的 Chunk 数量，由 RenderingRange 决定
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ChunkNum;

	/**
	 * @brief 实例化静态网格体 Map
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int32, UInstancedStaticMeshComponent*> InstancedMeshComponents;

	/**
	 * @brief 渲染区块数
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int RenderingRange = 48;

	/**
	 * @brief 上次更新时 Player 所在 Chunk 的 XY 轴坐标
	 * TODO 更新为 Pari<int, int>
	 */
	UPROPERTY(BlueprintReadOnly)
	FVector2D LastPlayerChunkCoordinate;

	/**
	 * @brief 区块 XY 方块数
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int ChunkWidth = 16;

	/**
	 * @brief 区块 Z 方块数
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int ChunkHeight = 312;
	
	/**
	 * @brief 每 Tick 都会触发，根据 ActorLocation 更新 Chunks
	 * @return 当 Player 移动一段距离后返回 true
	 */
	UFUNCTION()
	bool ShouldUpdatePlayerCoordinate();

	/**
	 * @brief 在 RenderingRange 内生成 Chunk
	 */
	UFUNCTION()
	void AddChunk();

	/**
	 * @brief 移除 RenderingRange 外的 Chunk  
	 */
	UFUNCTION()
	void RemoveChunk() const;

	/**
	 * @brief 将 ChunkSize 由方块数换算成实际大小(cm)
	 * @return ChunkSize * 100
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetChunkRealWidth() const;

	/**
	 * @brief 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector ChunkIndexToRealPosition(const int X, const int Y) const;

	UFUNCTION(BlueprintCallable)
	void UpdateBlocks();

	UFUNCTION()
	UChunkComponent* GenerateChunk(const FVector2D& Location);

	UFUNCTION(BlueprintNativeEvent)
	void InitInstancedMeshComponents();

	UFUNCTION(BlueprintCallable)
	inline float GetCountTime() const { return CountTime; }

	UFUNCTION(BlueprintCallable)
	inline float GetUpdateTime() const { return UpdateTime; }

protected:
	bool UpdateTimer(float DeltaTime);
	
private:
	/**
	 * @brief 更新计时
	 */
	float CountTime;

	/**
	 * @brief 更新间隔
	 */
	float UpdateTime;
};
