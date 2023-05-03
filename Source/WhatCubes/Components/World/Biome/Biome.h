#pragma once
#include "BiomeTypes.h"
#include "WhatCubes/Components/Pre.h"
#include "WhatCubes/Components/Lang/Optional.h"

class Biome
{
public:
	/**
	 * @brief 
	 * @param Rhs 
	 */
	Biome(BiomeType Rhs);
	/**
	 * @brief 
	 * @return 
	 */
	BiomeType GetBiomeType() const;
	/**
	 * @brief 
	 * @param Rhs 
	 */
	void SetBiomeType(BiomeType Rhs);
	/**
	 * @brief 
	 * @param Rhs 
	 * @return 
	 */
	Optional<BiomeType> SetBiomeType(IndexType Rhs);
private:
	BiomeType Type;
};
