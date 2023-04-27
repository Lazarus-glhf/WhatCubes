// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMeshData.generated.h"

USTRUCT(BlueprintType)
struct FMeshData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> Triangles;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> UV0;

	UPROPERTY(BlueprintReadOnly)
	TArray<FColor> BlockVertexColors;
};