#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <cctype>

#include "Biome.h"
#include "WhatCubes/Components/Pre.h"
#include "WhatCubes/Components/Lang/Optional.h"
#include "BiomeTypes.h"
#include "WhatCubes/Components/Maths/MathUtils.h"

class Biomes
{
public:
	/**
	 * @brief 
	 * @return 
	 */
	static Biomes& GetInstance();
	/**
	 * @brief 
	 * @param Name 
	 * @return 
	 */
	Optional<BiomeType> GetBiomeTypeByName(std::string&& Name) const;
	/**
	 * @brief 
	 * @param Rhs 
	 * @return 
	 */
	static IndexType IndexFromBiomeType(BiomeType Rhs);
	/**
	 * @brief 
	 * @param Rhs 
	 * @return 
	 */
	static IndexType IndexFromBiomeType(Optional<BiomeType> Rhs);
	/**
	 * @brief 
	 * @param Seed 
	 * @param Pos 
	 * @return 
	 */
	Biome GetBiome(SeedType Seed, MathUtils::Coord Pos);
	/**
	 * @brief 
	 * @param BiomeX 
	 * @param BiomeY 
	 * @param BiomeZ 
	 * @return 
	 */
	Biome GetBiomeForNoiseGen(CoordInt BiomeX, CoordInt BiomeY, CoordInt BiomeZ);
private:
	Biomes() = default;
	/**
	 * @brief 
	 */
	std::unordered_map<std::string, BiomeType> Name2Idx;
};
