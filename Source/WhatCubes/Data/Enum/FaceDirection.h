// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	Forward,
	Right,
	Back,
	Left,
	Up,
	Down
};