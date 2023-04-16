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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UClass* ActorToSpawn;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector2D, AChunk*> AllChunks;

	UFUNCTION()
	bool UpdateLocation();

	UFUNCTION()
	void AddChunk();

	UFUNCTION()
	void RemoveChunk();

private:
	FVector2D ChunkLocation;

	float ChunkSize;

	float RenderingRange;

};
