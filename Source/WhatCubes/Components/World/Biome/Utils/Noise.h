#pragma once

#include "WhatCubes/Components/Pre.h"

class Noise
{
public:
	/**
	 * @brief 
	 * @param Seed 
	 * @param I 
	 * @param J 
	 * @param K 
	 * @param D 
	 * @param E 
	 * @param F 
	 * @return 
	 */
	static Double Method38106(SeedType Seed, int I, int J, int K, Double D, Double E, Double F);
	/**
	 * @brief 
	 * @param Seed 
	 * @return 
	 */
	static Double Method38108(SeedType Seed);
	/**
	 * @brief 
	 * @param Seed 
	 * @param Salt 
	 * @return 
	 */
	static SeedType MixSeed(SeedType Seed, SeedType Salt);
};
