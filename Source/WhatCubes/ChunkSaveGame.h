// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enum/BlockType.h"
#include "GameFramework/SaveGame.h"
#include "ChunkSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class WHATCUBES_API UChunkSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<EBlockType> Blocks;
	
};
