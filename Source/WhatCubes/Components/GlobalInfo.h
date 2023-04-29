// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkComponent.h"
#include "Components/ActorComponent.h"
#include "WhatCubes/Data/Enum/BlockType.h"
#include "GlobalInfo.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WHATCUBES_API UGlobalInfo : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGlobalInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, EBlockType> GlobalBlocksID;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, EBlockType> BlocksNeedToCreate;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, EBlockType> BlocksCreated;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FVector2D, UChunkComponent*> ChunksLoaded;
};
