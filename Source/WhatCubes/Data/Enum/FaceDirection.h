// Fill out your copyright notice in the description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * @brief
 */
UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	Forward, // 前
	Right,	// 右
	Back,	// 后
	Left,	// 左
	Up,		// 上
	Down	// 下
};