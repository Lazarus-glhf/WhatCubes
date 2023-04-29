#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EBlockType : uint32
{
	None,
	Air,
	Stone,
	Dirt,
	Grass,
	BedRock
};