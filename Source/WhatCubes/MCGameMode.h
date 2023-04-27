// Fill out your copyright notice in the briefription page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Chunk.h"
#include "MCGameMode.generated.h"

/**
 * %class
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
	 * %member
	 * @brief 维护的 Chunk 数量，由 RenderingRange 决定
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ChunkNum;

	/**
	 * %member
	 * @brief
	 * Chunk Map
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FVector2D, AChunk*> AllChunks;

	/**
	 * %member
	 * @brief
	 * 渲染距离
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RenderingRange;

	/**
	 * %method
	 * @brief
	 * 每 Tick 都会触发，根据 ActorLocation 更新 ChunkLocation
	 * @return
	 * 当 Player 移动一段距离后返回 true
	 */
	UFUNCTION()
	bool UpdateLocation();

	/**
	 * %method
	 * @brief
	 * 在 RenderingRange 内生成 Chunk
	 */
	UFUNCTION()
	void AddChunk();

	/**
	 * %method
	 * @brief
	 * 移除 RenderingRange 外的 Chunk  
	 */
	UFUNCTION()
	void RemoveChunk();

	UFUNCTION(BlueprintNativeEvent)
	AChunk* GenerateChunk(const FVector& Location);
	
private:
	/**
	 * %member
	 * @brief
	 * 区块中心
	 */
	FVector2D ChunkLocation;

	/**
	 * %member
	 * @brief
	 * 区块大小
	 */
	float ChunkSize;
};
