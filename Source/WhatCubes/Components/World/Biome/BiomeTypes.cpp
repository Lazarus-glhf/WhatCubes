#include "BiomeTypes.h"

Optional<BiomeType> BiomeTypes::TryFrom(IndexType Rhs)
{
	switch (Rhs)
	{
	case 0:
		return {BiomeType::PLAIN};
	case 1:
		return {BiomeType::DESERT};
	case 2:
		return {BiomeType::RIVER};
	default:
		return {};
	}
}
