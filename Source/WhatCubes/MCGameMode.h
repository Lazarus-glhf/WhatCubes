// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Chunk.h"
#include "MCGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WHATCUBES_API AMCGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	AMCGameMode();

	/**
	 * @desc 维护的 Chunk 数量，由 RenderingRange 决定
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ChunkNum;

	/**
	 * %member
	 * @desc
	 * Chunk Map
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FVector2D, AChunk*> AllChunks;

	/**
	 * %member
	 * @desc
	 * 渲染距离
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RenderingRange;

	/**
	 * %method
	 * @desc
	 * 每 Tick 都会触发，根据 ActorLocation 更新 ChunkLocation
	 * @return 当 Player 移动一段距离后返回 true
	 */
	UFUNCTION()
	bool UpdateLocation();

	/**
	 * %method
	 * @desc
	 * 在 RenderingRange 内生成 Chunk
	 */
	UFUNCTION()
	void AddChunk();

	/**
	 * %method
	 * @desc
	 * 移除 RenderingRange 外的 Chunk  
	 */
	UFUNCTION()
	void RemoveChunk();

	UFUNCTION(BlueprintNativeEvent)
	AChunk* GenerateChunk(const FVector& Location);
	
private:
	/**
	 * %member
	 * @desc
	 * 区块中心
	 */
	FVector2D ChunkLocation;

	/**
	 * %member
	 * @desc
	 * 区块大小
	 */
	float ChunkSize;
};
