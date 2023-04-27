#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	None,
	Air,
	Stone,
	Dirt,
	Grass,
	BedRock
};